#ifndef MESH_H
#define MESH_H

#include "Shader.h"
#include <glm/glm.hpp>

using namespace std;

class Mesh {
private:
	unsigned int VBO, EBO;

	/*  Default mesh data  */
	float vertices[20] = {
		// positions          // texture coords
		-0.5f,  0.2f, 0.0f,  -0.05f,  1.01f, // top left
		-0.5f, -0.2f, 0.0f,  -0.05f, -0.01f, // bottom left
		-0.4f, -0.2f, 0.0f,   1.05f, -0.01f, // bottom right
		-0.4f,  0.2f, 0.0f,   1.05f,  1.01f  // top right
	};

	unsigned int indices[6] = {
		0, 1, 2, // first triangle
		2, 3, 0  // second triangle
	};

public:
	unsigned int VAO;

	Mesh() { }
	~Mesh();

	void setupMesh();
	void setVertices(int index, int barNum);
	void draw(Shader shader);
	void loadTexture(const char *path);
};

#endif



