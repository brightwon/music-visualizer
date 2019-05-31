#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

class Shader
{
private:
	// load shader files
	std::string loadVertexShader(const char* vertexPath);
	std::string loadFragmentShader(const char* fragmentPath);

public:
	Shader(const char* vertexPath, const char* fragmentPath);

	// program ID
	unsigned int ID;

	// activate and use the shader
	void use();

	// uniforms utility functions
	void setFloat(const std::string &name, float value) const;
};

#endif