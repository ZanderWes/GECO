#pragma once
#include <glm.hpp>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <GL/freeglut.h>
#include <GL/GL.h>


typedef GLfloat vec2_t[2];
typedef GLfloat vec3_t[3];

//header data
struct MDHeader
{
	int ident;                  // magic number: "IDP2" 
	int version;                // version: must be 8 

	int skinwidth;              // texture width 
	int skinheight;             // texture height 

	int framesize;              // size in bytes of a frame 

	int num_skins;              // number of skins 
	int num_vertices;           // number of vertices per frame 
	int num_st;                 // number of texture coordinates
	int num_tris;               // number of triangles 
	int num_glcmds;             // number of opengl commands 
	int num_frames;             // number of frames 

	int offset_skins;           // offset skin data 
	int offset_st;              // offset texture coordinate data 
	int offset_tris;            // offset triangle data 
	int offset_frames;          // offset frame data 
	int offset_glcmds;          // offset OpenGL command data 
	int offset_end;             // offset end of file 
};

//skin texture file name
struct MDSkin
{
	char name[64];
};

//texture coordinates
struct MDTexTureCoordinates
{
	short s;
	short t;
};

//triangles
struct MDTriangle
{
	unsigned short vertex[3];
	unsigned short st[3];
};

//compressed vertex data
struct MDVertex
{
	unsigned char v[3];
	unsigned char normalindex;
};

//model frames
struct MDFrame
{
	~MDFrame() { delete[] vertices; }

	vec3_t scale;
	vec3_t translate;
	char name[16];				 // frame name
	struct MDVertex* vertices;	 // list of vrame vertices
};

//opengl commands
struct MDGLCommands
{
	float s_texcoord;
	float t_texcoord;
	int index;
};

// animation info
struct MDAnimation
{
	//first frame
	int start;
	//last frame
	int end;
};

class ModelMD
{
public:

	ModelMD(const char* filename);
	~ModelMD();

	typedef std::map<std::string, unsigned int> SkinMap;
	typedef std::map<std::string, MDAnimation> AnimMap;

	bool loadTexture(const std::string& filename);

	void renderFrameImmediate(int frame);

	void setScale(GLfloat scale) { scale_ = scale; }
	void setTranslation(glm::fvec3 translate);
	glm::fvec3 getTranslate() { return glm::fvec3 { position_[1], position_[2], position_[0] }; }
	int getFramecount() { return header_.num_frames; }

	// Accessors
	const SkinMap& skins() const { return skin_ids_; }
	const AnimMap& anims() const { return animations_; }

private:
	void setupAnimations();

	vec3_t normals_[162];

	// Model data
	MDHeader header_;
	MDSkin* skins_;
	MDTexTureCoordinates* texCoords_;
	MDTriangle* triangles_;
	MDFrame* frames_;
	int* opengl_commands_;

	GLfloat scale_;

//due to decompression    Z    X    Y
	vec3_t position_ = {600, 900, 0};

	GLuint texture_;
	SkinMap skin_ids_;
	AnimMap animations_;
};

class Md2Object
{
public:
	// Public internal types/enums
	enum Md2RenderMode
	{
		kDrawImmediate = 0,
		kDrawGLcmds,
	};

public:
	
	Md2Object();

	Md2Object(ModelMD* model);
	
	~Md2Object() {};

public:

	void drawObjectFrame(int frame);
	
	void setModel(ModelMD* model);
	void setScale(float scale) { object_scale_ = scale; }
	void setTranslate(glm::fvec3 translate) { model_->setTranslation(translate); }
	glm::fvec3 getTranslate() { return model_->getTranslate(); }

	// Accessors
	const ModelMD* model() const { return model_; }
	float scale() const { return object_scale_; }

private:
	
	ModelMD* model_;
	float object_scale_;
	const MDAnimation* animation_info_;
	std::string current_animation_;
};