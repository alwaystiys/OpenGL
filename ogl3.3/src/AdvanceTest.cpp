#include "AdvanceTest.h"

using namespace AdvanceTest;
extern float g_cube_notex_vertices[288];
extern float g_plane_vertices[30];

DepthTesting::DepthTesting(){
    m_shader = NULL;
}

DepthTesting::~DepthTesting() {
    delete m_shader;
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &planeVBO);
}

bool DepthTesting::Init() {
    m_shader = new CommonShader(NULL, NULL, "../Shader/depth_testing.vs", "../Shader/depth_testing.fs");
    if(!m_shader->Init()) {
        return false;
    }
    // init cubeVAO
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_notex_vertices), g_cube_notex_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    // init planeVAO
    glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_plane_vertices), g_plane_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
    glBindVertexArray(0);
	// init texture
	cubeTexture = new Texture("../resources/textures/marble.jpg");
	floorTexture = new Texture("../resources/textures/metal.png");
	cubeTexture->Load();
	floorTexture->Load();
	// init shader
	m_shader->Enable();
	m_shader->setUniform1i("texture1", 0);
    return true;
}

void DepthTesting::RenderSceneCB() {
    m_shader->Enable();
	
    Transform view(camera.GetViewMatrix());
    Transform projection(libmath::genPerspective(libmath::toRadians(camera.zoom), (float) 800 / 600, 1.0f, 100.0f));
    m_shader->setUniformMatrix4fv("view", view.getTransformResult());
	m_shader->setUniformMatrix4fv("projection", projection.getTransformResult());
	// cubes
	glBindVertexArray(cubeVAO);
	cubeTexture->Bind(GL_TEXTURE0);

	Transform transform;
	transform.translate(-1.0f, 0.0f, -1.0f);
    m_shader->setUniformMatrix4fv("model", transform.getTransformResult());
    glDrawArrays(GL_TRIANGLES, 0, 36);

	//Transform transform;
	transform.reset();
	transform.translate(2.0f, 0.0f, 0.0f);
    m_shader->setUniformMatrix4fv("model", transform.getTransformResult());
    glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	// planes
	glBindVertexArray(planeVAO);
	floorTexture->Bind(GL_TEXTURE0);

	//Transform transform;
	transform.reset();
    m_shader->setUniformMatrix4fv("model", transform.getTransformResult());
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
