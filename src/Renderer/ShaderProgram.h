#pragma once
#include<iostream>
#include<string>
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/mat4x4.hpp>

using namespace std;
namespace Renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const string& vertexShader,
			const string& fragmentShader);
		 ~ShaderProgram();
		 bool isCompiled()const { return m_isCompiled; }
		 void use()const;
		 void setInt(const string& name, const GLint value);
		 void setmMatrix4(const string&name,const glm::mat4 &matrix);


		 ShaderProgram() = delete;
		 ShaderProgram(ShaderProgram&) = delete;
		 ShaderProgram& operator=(const ShaderProgram&) = delete;
		 ShaderProgram& operator =(ShaderProgram&& shaderProgram)noexcept;//move constructor
		 ShaderProgram(ShaderProgram&& shaderProgram)noexcept;//move constructor
		
		 

	private:
		bool createShader(const string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_isCompiled = false;
		GLuint m_ID = 0 ;

	};
}
