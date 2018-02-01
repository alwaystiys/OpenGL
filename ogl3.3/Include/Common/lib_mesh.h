#ifndef LIB_MESH_H
#define LIB_MESH_H

#include "Common/lib_math.h"
#include <string>
#include "Common/shader_basic.h"
#include <vector>

// ��������ÿ����������
struct Vertex{
	vec3 position;
	vec3 normal;
	vec2 texCoords;
	vec3 tangent;
	vec3 bitangent;
};

// 
struct Texture{
	unsigned int id;
	std::string type;
	std::string path;
};


class Mesh{
	/*  ��������  */
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        /*  ����  */
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(ShaderBasic shader);
    private:
        /*  ��Ⱦ����  */
        unsigned int VAO, VBO, EBO;
        /*  ����  */
        void setupMesh();


};














#endif LIB_MESH_H