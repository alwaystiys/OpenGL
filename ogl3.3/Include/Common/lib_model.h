#ifndef LIB_MODEL_H
#define LIB_MODEL_H

#include "Common/lib_mesh.h"
#include "Common/shader_basic.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
    /*  Model Data */
    vector<MeshTexture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection; //Ù¤ÂêÐÞÕý

    /*  Functions   */
    // constructor, expects a filepath to a 3D model.
    Model(string const &path, bool gamma = false);
    void Draw(ShaderBasic shader);
private:
    /*  º¯Êý   */
    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<MeshTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif LIB_MODEL_H