#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{	
	std::string vString = loadVertexShader(vertexPath);
	const char* vShaderCode = vString.c_str();

	std::string fString = loadFragmentShader(fragmentPath);
	const char* fShaderCode = fString.c_str();

	unsigned int vertex, fragment;

	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


/* load Vertex Shader file */
std::string Shader::loadVertexShader(const char* vertexPath) {
	std::string vertexCode;
	std::ifstream vShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);

		std::stringstream vShaderStream;
		vShaderStream << vShaderFile.rdbuf();

		vShaderFile.close();

		vertexCode = vShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::Can't read the file" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	return vShaderCode;
}


/* load Fragment Shader file */
std::string Shader::loadFragmentShader(const char* fragmentPath) {
	std::string fragmentCode;
	std::ifstream fShaderFile;

	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		fShaderFile.open(fragmentPath);

		std::stringstream fShaderStream;
		fShaderStream << fShaderFile.rdbuf();

		fShaderFile.close();

		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::Can't read the file" << std::endl;
	}
	const char* fShaderCode = fragmentCode.c_str();
	return fShaderCode;
}


void Shader::use() {
	glUseProgram(ID);
}

void Shader::setFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}