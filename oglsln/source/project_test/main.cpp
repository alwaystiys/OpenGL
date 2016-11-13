/*

	Copyright 2011 Etay Meiri

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_util.h"
#include "ogldev_app.h"
#include "shader_technique.h"
#include "ogldev_camera.h"
#include "ogldev_glut_backend.h"
#include "ogldev_pipeline.h"
#include "ogldev_texture.h"

#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 540
#define WINDOW_TITLE "Test For OpenGL"


struct Vertex {
	Vector3f m_pos;
	Vector2f m_tex;
	Vertex(){}
	Vertex(Vector3f pos, Vector2f tex){
		m_pos = pos;	
		m_tex = tex;
	}
};


class TemplateMain : public ICallbacks, public OgldevApp
{
public:

	TemplateMain()
	{
		m_pEffect = NULL;
		m_pCamera = NULL;
		m_pTexture = NULL;
		m_persProjInfo.FOV = 30.0f;
		m_persProjInfo.Height = WINDOW_HEIGHT;
		m_persProjInfo.Width = WINDOW_WIDTH;
		m_persProjInfo.zNear = 1.0f;
		m_persProjInfo.zFar = 100.0f;
	}

	~TemplateMain()
	{
		delete m_pEffect;
		delete m_pCamera;
		delete m_pTexture;
	}

	bool Init()
	{
		Vector3f pos(0.0f, 0.0f, 20.0f);
		Vector3f target(0.0f, 0.0f, -1.0f);
		Vector3f up(0.0f, 5.0f, 0.0f);
		m_pCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, pos, target, up);
		m_pTexture = new Texture(GL_TEXTURE_2D, "../../content/test.png");
		if (!m_pTexture->Load()) {
			return 1;
		}
		m_pTexture->Bind(GL_TEXTURE0);
		m_pEffect = new ShaderTechnique();	
		if (!m_pEffect->Init()){
			printf("Error initializing the lighting technique\n");
			return false;	
		}
		m_pEffect->Enable();

		CreateVertexBuffer();
		CreateIndiceBuffer();

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		return true;
	}

	void Run()
	{
		GLUTBackendRun(this);
	}

	virtual void RenderSceneCB()
	{
		m_pCamera->OnRender();
		glClear(GL_COLOR_BUFFER_BIT);

		static float Scale = 0.0f;
		Scale += 0.1f;
	
		Pipeline p;
		p.Rotate(0.0f, Scale, 0.0f);
		p.WorldPos(0.0f, 0.0f, 5.0f);
		p.SetCamera(m_pCamera->GetPos(), m_pCamera->GetTarget(), m_pCamera->GetUp());
		p.SetPerspectiveProj(m_persProjInfo);
		m_pEffect->setWorldMatrix(p.GetWVPTrans());
		m_pEffect->setSampler(0);
		
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		GLUTBackendSwapBuffers();
	}

	virtual void KeyboardCB(OGLDEV_KEY OgldevKey)
    {
        switch (OgldevKey) {
            case OGLDEV_KEY_ESCAPE:
            case OGLDEV_KEY_q:
                    GLUTBackendLeaveMainLoop();
                    break;
            case OGLDEV_KEY_a:
                break;
            case OGLDEV_KEY_s:
                break;
            case OGLDEV_KEY_z:
                break;
            case OGLDEV_KEY_x:
                break;
        }
    }

    virtual void PassiveMouseCB(int x, int y)
    {
        m_pCamera->OnMouse(x, y);
    }

private:
	void CreateVertexBuffer()
	{
		Vertex vertices[5] = {
			Vertex(Vector3f(-1.0f, -1.0f, -1.0f), Vector2f(0.0f, 0.0f)),
			Vertex(Vector3f(-1.0f, -1.0f, 1.0f), Vector2f(0.5f, 0.0f)),
			Vertex(Vector3f(1.0f, -1.0f, 1.0f), Vector2f(1.0f, 0.0f)),
			Vertex(Vector3f(1.0f, -1.0f, -1.0f), Vector2f(0.5f, 1.0f)),
			Vertex(Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 0.0f))
		};

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}

	void CreateIndiceBuffer(){
		unsigned int indices[] = {
			0, 4, 1,
			1, 4, 2,
			2, 4, 3,
			3, 4, 0,
			0, 1, 2,
			0, 2, 3,
		};
		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;
	ShaderTechnique* m_pEffect;
	PersProjInfo m_persProjInfo;
	Camera *m_pCamera;
	Texture *m_pTexture;
};


int main(int argc, char** argv)
{
	GLUTBackendInit(argc, argv, false, false);

	if (!GLUTBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, WINDOW_TITLE)) {
		return 1;
	}

	TemplateMain* pApp = new TemplateMain();

	if (!pApp->Init()) {
		return 1;
	}

	pApp->Run();

	delete pApp;

	return 0;
}