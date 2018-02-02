#ifndef LIB_MESH_H
#define LIB_MESH_H

#include "Common/lib_math.h"
#include <string>
#include "Common/shader_basic.h"
#include <vector>
using namespace std;

class Mesh{
	// 用来索引每个顶点属性
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
	/*  网格数据  */
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;
        /*  函数  */
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        void Draw(ShaderBasic shader);
    private:
        /*  渲染数据  */
        unsigned int VAO, VBO, EBO;
        /*  函数  */
        void setupMesh();
};














#endif LIB_MESH_H