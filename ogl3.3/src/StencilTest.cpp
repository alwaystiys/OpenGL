#include "StencilTest.h"

using namespace StencilTest;
extern float g_cube_notex_vertices[288];
extern float g_plane_vertices[30];

StencilTesting::StencilTesting() {
    m_shader = NULL;
    m_outline_shader = NULL;
}

StencilTesting::~StencilTesting() {
    delete m_shader;
    delete m_outline_shader;
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &planeVBO);
}

bool StencilTesting::Init() {
    m_shader = new CommonShader(NULL, NULL, "../Shader/stencil_testing.vs", "../Shader/stencil_testing.fs");
    m_outline_shader = new CommonShader(NULL, NULL, "../Shader/stencil_testing.vs", "../Shader/stencil_single_color.fs");
    if(!m_shader->Init()) {
        return false;
    }
    if(!m_outline_shader->Init()) {
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

void StencilTesting::PreRenderConfig() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void StencilTesting::GLClearConfig() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // don't forget to clear the stencil buffer!
}

void StencilTesting::RenderSceneCB() {
    //
    m_shader->Enable();
    Transform view(camera.GetViewMatrix());
    Transform projection(libmath::genPerspective(libmath::toRadians(camera.zoom), (float) 800 / 600, 1.0f, 100.0f));
    m_shader->setUniformMatrix4fv("view", view.getTransformResult());
    m_shader->setUniformMatrix4fv("projection", projection.getTransformResult());
    //
    m_outline_shader->Enable();
    m_outline_shader->setUniformMatrix4fv("view", view.getTransformResult());
    m_outline_shader->setUniformMatrix4fv("projection", projection.getTransformResult());
    // draw floor as normal, but don't write the floor to the stencil buffer,
    // we only care about the containers. We set its mask to 0x00 to not write to the stencil buffer.
    glStencilMask(0x00);
    //
    Transform transform;
    // planes
    glBindVertexArray(planeVAO);
    floorTexture->Bind(GL_TEXTURE0);
    //Transform transform;
    m_shader->Enable();
    m_shader->setUniformMatrix4fv("model", transform.getTransformResult());
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    //
    // 1st. render pass, draw objects as normal, writing to the stencil buffer
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    // cubes
    glBindVertexArray(cubeVAO);
    cubeTexture->Bind(GL_TEXTURE0);
    transform.reset();
    transform.translate(-1.0f, 0.01f, -1.0f);
    m_shader->setUniformMatrix4fv("model", transform.getTransformResult());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    //Transform transform;
    transform.reset();
    transform.translate(2.0f, 0.01f, 0.0f);
    m_shader->setUniformMatrix4fv("model", transform.getTransformResult());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    // 2nd. render pass: now draw slightly scaled versions of the objects, this time disabling stencil writing.
    // Because the stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are not drawn, thus only drawing
    // the objects' size differences, making it look like borders.
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    m_outline_shader->Enable();
    float scale = 1.1;
    // cubes
    glBindVertexArray(cubeVAO);
    cubeTexture->Bind(GL_TEXTURE0);
    transform.reset();
    transform.translate(-1.0f, 0.0f, -1.0f).scale(scale, scale, scale);
    m_outline_shader->setUniformMatrix4fv("model", transform.getTransformResult());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    transform.reset();
    transform.translate(2.0f, 0.0f, 0.0f).scale(scale, scale, scale);
    m_outline_shader->setUniformMatrix4fv("model", transform.getTransformResult());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glStencilMask(0xFF);
    glEnable(GL_DEPTH_TEST);
}