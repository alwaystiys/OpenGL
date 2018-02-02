#ifndef LIB_MODEL_H
#define LIB_MODEL_H

#include "Common/lib_mesh.h"
#include "Common/shader_basic.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class Model 
{
    public:
        /*  ����   */
        Model(char *path)
        {
            loadModel(path);
        }
		void Draw(ShaderBasic shader);   
    private:
        /*  ģ������  */
        vector<Mesh> meshes;
        string directory;
        /*  ����   */
        void loadModel(string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif LIB_MODEL_H