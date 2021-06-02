
#ifdef _WIN32
#define	WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "ModelMD.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/GL.h>
#include <iostream>
#include <fstream>
#include <SOIL.h>

using std::cout;
using std::cerr;
using std::endl;


/***************************************
 * MD2 model
***************************************/
ModelMD::ModelMD(const char* filename)
	: skins_(NULL), texCoords_(NULL), triangles_(NULL), frames_(NULL),
	opengl_commands_(NULL), scale_(1.0f)
{
	// Open the file
	std::ifstream ifs(filename, std::ios::binary);

	if (ifs.fail())
		throw std::runtime_error("Couldn't open file");

	// Read header
	ifs.read(reinterpret_cast<char*>(&header_), sizeof(MDHeader));

	// Check if ident and version are valid
	if (header_.ident != 844121161)
		throw std::runtime_error("Bad file ident");

	if (header_.version != 8)
		throw std::runtime_error("Bad file version");

	// Memory allocation for model data
	skins_ = new MDSkin[header_.num_skins];
	texCoords_ = new MDTexTureCoordinates[header_.num_st];
	triangles_ = new MDTriangle[header_.num_tris];
	frames_ = new MDFrame[header_.num_frames];
	opengl_commands_ = new int[header_.num_glcmds];

	// Read skin names
	ifs.seekg(header_.offset_skins, std::ios::beg);
	ifs.read(reinterpret_cast<char*>(skins_), sizeof(MDSkin) * header_.num_skins);

	// Read texture coords.
	ifs.seekg(header_.offset_st, std::ios::beg);
	ifs.read(reinterpret_cast<char*>(texCoords_), sizeof(MDTexTureCoordinates) * header_.num_st);

	// Read triangle data
	ifs.seekg(header_.offset_tris, std::ios::beg);
	ifs.read(reinterpret_cast<char*>(triangles_), sizeof(MDTriangle) * header_.num_tris);

	// Read frames
	ifs.seekg(header_.offset_frames, std::ios::beg);
	for (int i = 0; i < header_.num_frames; ++i)
	{
		// Memory allocation for the vertices of this frame
		frames_[i].vertices = new MDVertex[header_.num_vertices];

		// Read frame data
		ifs.read(reinterpret_cast<char*>(&frames_[i].scale), sizeof(vec3_t));
		ifs.read(reinterpret_cast<char*>(&frames_[i].translate), sizeof(vec3_t));
		ifs.read(reinterpret_cast<char*>(&frames_[i].name),	sizeof(char) * 16);
		ifs.read(reinterpret_cast<char*>(frames_[i].vertices), sizeof(MDVertex) * header_.num_vertices);
	}

	// Read OpenGL commands
	ifs.seekg(header_.offset_glcmds, std::ios::beg);
	ifs.read(reinterpret_cast<char*>(opengl_commands_), sizeof(int) * header_.num_glcmds);

	// Close file
	ifs.close();

	// Setup animation infos
	setupAnimations();
}

ModelMD::~ModelMD()
{
	delete[] skins_;
	delete[] texCoords_;
	delete[] triangles_;
	delete[] frames_;
	delete[] opengl_commands_;
}

bool ModelMD::loadTexture(const std::string& filename)
{
	const char* file = filename.c_str();

	GLuint text = SOIL_load_OGL_texture(file, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	if (!text)
	{
		cout << "error loading immage" ;
		return false;
	}
	else
	{
		texture_ = text;
		//_skinIds.insert(SkinMap::value_type(filename, text));
	}

	return (true);
}

void ModelMD::setTranslation(glm::fvec3 translate)
{
	// due to the way that decompression is done
	position_[0] += translate[2];
	position_[1] += translate[0];
	position_[2] = translate[1] + 45;
}

void ModelMD::setupAnimations()
{
	std::string currentAnim;
	MDAnimation animInfo = { 0, 0 };

	for (int i = 0; i < header_.num_frames; ++i)
	{
		std::string frameName = frames_[i].name;
		std::string frameAnim;

		// Extract animation name from frame name
		std::string::size_type len = frameName.find_first_of("0123456789");
		if ((len == frameName.length() - 3) &&
			(frameName[len] != '0'))
			len++;

		frameAnim.assign(frameName, 0, len);

		if (currentAnim != frameAnim)
		{
			if (i > 0)
			{
				// Previous animation is finished, insert
				// it and start new animation.
				animations_.insert(AnimMap::value_type
				(currentAnim, animInfo));
			}

			// Initialize new anim info
			animInfo.start = i;
			animInfo.end = i;

			currentAnim = frameAnim;
		}
		else
		{
			animInfo.end = i;
		}
	}

	// Insert last animation
	animations_.insert(AnimMap::value_type(currentAnim, animInfo));
}

void ModelMD::renderFrameImmediate(int frame)
{
	// Compute max frame index
	int maxFrame = header_.num_frames - 1;

	// Check if the frame index is valid
	if ((frame < 0) || (frame > maxFrame))
		return;

	// Bind to model's texture
	
	glBindTexture(GL_TEXTURE_2D, texture_);

	glBegin(GL_TRIANGLES);
	// Draw each triangle
	for (int i = 0; i < header_.num_tris; ++i)
	{
		// Draw each vertex of this triangle
		for (int j = 0; j < 3; ++j)
		{
			MDFrame* pFrame = &frames_[frame];
			MDVertex* pVert = &pFrame->vertices[triangles_[i].vertex[j]];
			MDTexTureCoordinates* pTexCoords = &texCoords_[triangles_[i].st[j]];

			// Compute final texture coords.
			GLfloat s = static_cast<GLfloat>(pTexCoords->s) / header_.skinwidth;
			GLfloat t = static_cast<GLfloat>(pTexCoords->t) / header_.skinheight;

			glTexCoord2f(s, 1.0f - t);

			// Send normal vector to OpenGL
			glNormal3fv(normals_[pVert->normalindex]);

			// Uncompress vertex position and scale it
			vec3_t v;

			v[0] = ((pFrame->scale[0] * pVert->v[0] + pFrame->translate[0]) * scale_) + position_[0];
			v[1] = ((pFrame->scale[1] * pVert->v[1] + pFrame->translate[1]) * scale_) + position_[1];
			v[2] = ((pFrame->scale[2] * pVert->v[2] + pFrame->translate[2]) * scale_) + position_[2];

			glVertex3fv(v);
		}
	}
	glEnd();
}

/***************************************
 * MD2 object
***************************************/
Md2Object::Md2Object()	: model_(NULL), object_scale_(1.0f)
{
}

Md2Object::Md2Object(ModelMD* model) : model_(model), object_scale_(1.0f)
{
	setModel(model);
}

void Md2Object::drawObjectFrame(int frame)
{
	glPushMatrix();
	// Axis rotation
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);

	// Set model scale factor
	model_->setScale(object_scale_);

	glPushAttrib(GL_POLYGON_BIT);
	glFrontFace(GL_CW);

	// Render the model
	model_->renderFrameImmediate(frame);

	// GL_POLYGON_BIT
	glPopAttrib();
	glPopMatrix();
}

void Md2Object::setModel(ModelMD* model)
{
	model_ = model;

	if (model_)
	{
		// Set first animation as default animation
		animation_info_ = &model_->anims().begin()->second;
		current_animation_ = model_->anims().begin()->first;
	}
}

