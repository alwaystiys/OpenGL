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

#include <limits.h>
#include <string.h>

#include "ogldev_util.h"
#include "shader_technique.h"


ShaderTechnique::ShaderTechnique()
{   
}

bool ShaderTechnique::Init()
{
    if (!Technique::Init()) {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "shader.vs")) {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "shader.fs")) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }

	m_uScaleLocation = GetUniformLocation("u_scale");
	//if(m_uScaleLocation == 0xFFFFFFFF){
	//	printf("u_scale init fail!\n");
	//	return false;
	//}
	m_uWorldLocation = GetUniformLocation("u_world");
	/*if(m_uWorldLocation == 0xFFFFFFFF){
		printf("u_world init fail!\n");
		return false;
	}*/

    return true;
}

void ShaderTechnique::setScalef(float f){
	glUniform1f(m_uScaleLocation, f);
}

void ShaderTechnique::setWorldMatrix(Matrix4f matf){
	glUniformMatrix4fv(m_uWorldLocation, 1, GL_TRUE, (const GLfloat*)matf);
}

