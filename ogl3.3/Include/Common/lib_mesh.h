#ifndef LIB_MESH_H
#define LIB_MESH_H

#include "Common/lib_math.h"
#include <string>
#include "Common/shader_basic.h"
#include <vector>
using namespace std;

// ��������ÿ����������
struct MeshVertex {
    vec3 position;
    vec3 normal;
    vec2 texCoords;
    vec3 tangent;
    vec3 bitangent;
};

//
struct MeshTexture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    /*  ��������  */
    vector<MeshVertex> vertices;
    vector<unsigned int> indices;
    vector<MeshTexture> textures;
    /*  ����  */
    Mesh(vector<MeshVertex> vertices, vector<unsigned int> indices, vector<MeshTexture> textures);
    void Draw(ShaderBasic shader);
private:
    /*  ��Ⱦ����  */
    unsigned int VAO, VBO, EBO;
    /*  ����  */
    void setupMesh();
};


#endif LIB_MESH_H