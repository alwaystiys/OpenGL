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
#include "ogldev_glut_backend.h"
#include "ogldev_pipeline.h"

#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 540
#define WINDOW_TITLE "Test For OpenGL"



class TemplateMain : public ICallbacks, public OgldevApp
{
public:

	TemplateMain()
	{
		m_pEffect = NULL;
		m_persProjInfo.FOV = 30.0f;
		m_persProjInfo.Height = WINDOW_HEIGHT;
		m_persProjInfo.Width = WINDOW_WIDTH;
		m_persProjInfo.zNear = 1.0f;
		m_persProjInfo.zFar = 100.0f;
	}

	~TemplateMain()
	{
		delete m_pEffect;
	}

	bool Init()
	{
		CreateVertexBuffer();
		CreateIndiceBuffer();
		m_pEffect = new ShaderTechnique();	
		m_pEffect->Enable();
		if (!m_pEffect->Init()){
			printf("Error initializing the lighting technique\n");
			return false;	
		}
		m_pEffect->Enable();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return true;
	}

	void Run()
	{
		GLUTBackendRun(this);
	}

	virtual void RenderSceneCB()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

		static float Scale = 0.0f;
		Scale += 0.1f;

		Pipeline p;
		p.Rotate(Scale, 0.0f, 0.0f);
		p.WorldPos(0.0f, 0.0f, 10.0f);
		p.SetPerspectiveProj(m_persProjInfo);
		m_pEffect->setWorldMatrix(p.GetWPTrans());
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

		GLUTBackendSwapBuffers();
	}

private:
	void CreateVertexBuffer()
	{
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		Vector3f vertivces[4];
		vertivces[0] = Vector3f(-1.0f, -1.0f, -1.0f);
		vertivces[1] = Vector3f(1.0f, -1.0f, -1.0f);
		vertivces[2] = Vector3f( 0.0f, -1.0f, 1.0f);
		vertivces[3] = Vector3f( 0.0f, 1.0f, 0.0f);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertivces), vertivces, GL_STATIC_DRAW);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void CreateIndiceBuffer(){
		unsigned int indices[] = {
			1, 3, 0,
			2, 3, 1,
			0, 3, 2,
			0, 2, 1
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