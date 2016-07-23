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

#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 540
#define WINDOW_TITLE "Test For OpenGL"

class TemplateMain : public ICallbacks, public OgldevApp
{
public:

    TemplateMain()
    {
       m_pEffect = NULL;
    }

    ~TemplateMain()
    {
		delete m_pEffect;
    }

    bool Init()
    {
		CreateVertexBuffer();
		m_pEffect = new ShaderTechnique();	
		m_pEffect->Enable();
		if (!m_pEffect->Init()){
			printf("Error initializing the lighting technique\n");
            return false;	
		}
		m_pEffect->Enable();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
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
		static float Scale = 0.0f;
		Scale += 0.001f;
		m_pEffect->setScalef(sinf(Scale));
		glDrawArrays(GL_TRIANGLES, 0, 3);
		GLUTBackendSwapBuffers();
    }

private:
    void CreateVertexBuffer()
    {
        glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		Vector3f vertivces[3];
		vertivces[0] = Vector3f(-1.0f, -1.0f, 0.0f);
		vertivces[1] = Vector3f( 0.0f, 1.0f, 0.0f);
		vertivces[2] = Vector3f( 1.0f, -1.0f, 0.0f);
		
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertivces), vertivces, GL_STATIC_DRAW);

		glDeleteVertexArrays(1, &m_VAO);
    }
	GLuint m_VAO;
    GLuint m_VBO;
	ShaderTechnique* m_pEffect;
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