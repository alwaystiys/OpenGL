#ifndef LIB_MESH_H
#define LIB_MESH_H

#include "Common/lib_math.h"
#include <string>
#include "Common/shader_basic.h"
#include <vector>
using namespace std;

class Mesh{
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

	public:
	/*  ��������  */
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;
        /*  ����  */
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        void Draw(ShaderBasic shader);
    private:
        /*  ��Ⱦ����  */
        unsigned int VAO, VBO, EBO;
        /*  ����  */
        void setupMesh();
};














#endif LIB_MESH_H