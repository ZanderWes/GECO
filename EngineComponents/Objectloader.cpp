#include "Objectloader.h"

/*
void ObjectLoader::loadMD2File(const char* filename, ModelMD* model)
{

    FILE* fp;
    int i;

    fp = fopen(filename, "rb");
    if (!fp)
    {
        std::cerr << "error opening file: " << filename << std::endl;
        return;
    }

    /* Read header *
    fread(&model->header, 1, sizeof(ModelMD::MDHeader), fp);

    if ((model->header.ident != 844121161) ||(model->header.version != 8))
    {
        std::cerr << "Error: bad version or identifier" << std::endl;
        fclose(fp);
        return;
    }

    /* Memory allocations *
    model->skins = (struct MDSkin*) malloc(sizeof(ModelMD::MDSkin) * model->header.num_skins);
    model->texcoords = (struct md2_texCoord_t*) malloc(sizeof(struct md2_texCoord_t) * model->header.num_st);
    model->triangles = (struct ModelMD*) malloc(sizeof(ModelMD::MDTriangle) * model->header.num_tris);
    model->frames = (struct md2_frame_t*)
        malloc(sizeof(struct md2_frame_t) * model->header.num_frames);
    model->glcmds = (int*)malloc(sizeof(int) * model->header.num_glcmds);

    /* Read model data *
    fseek(fp, model->header.offset_skins, SEEK_SET);
    fread(model->skins, sizeof(ModelMD::MDSkin),
        model->header.num_skins, fp);

    fseek(fp, model->header.offset_st, SEEK_SET);
    fread(model->texcoords, sizeof(struct md2_texCoord_t),
        model->header.num_st, fp);

    fseek(fp, model->header.offset_tris, SEEK_SET);
    fread(model->triangles, sizeof(struct md2_triangle_t),
        model->header.num_tris, fp);

    fseek(fp, model->header.offset_glcmds, SEEK_SET);
    fread(model->glcmds, sizeof(int), model->header.num_glcmds, fp);

    /* Read frames *
    fseek(fp, model->header.offset_frames, SEEK_SET);
    for (i = 0; i < model->header.num_frames; ++i)
    {
        /* Memory allocation for vertices of this frame */
        model->frames[i].verts = (struct md2_vertex_t*)
            malloc(sizeof(struct md2_vertex_t) * model->header.num_vertices);

        /* Read frame data *
        fread(model->frames[i].scale, sizeof(glm::fvec3), 1, fp);
        fread(model->frames[i].translate, sizeof(glm::fvec3), 1, fp);
        fread(model->frames[i].name, sizeof(char), 16, fp);
        fread(model->frames[i].verts, sizeof(struct md2_vertex_t),
            model->header.num_vertices, fp);
    }

    fclose(fp);
    return;
}*/