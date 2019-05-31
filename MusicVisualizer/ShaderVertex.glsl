#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform float targetPos;

void main() {
	gl_Position = vec4(aPos.x, (aPos.y * targetPos), aPos.z, 1.0);
	TexCoord = aTexCoord;
}