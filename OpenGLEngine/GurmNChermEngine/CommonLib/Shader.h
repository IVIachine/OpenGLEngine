#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <GL/glew.h>
#include "Transform.h"
#include "Camera.h"
//Cite::https://www.youtube.com/watch?v=csKrVBWCItc&list=PLEETnX-uPtBXT9T-hD0Bj31DSnwio-ywh&index=7
class Shader
{
private:
	static const unsigned int NUM_SHADERS = 2;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint m_uniforms[NUM_UNIFORMS];

public:
	Shader(const std::string& fileName);
	Shader() {};
	~Shader();

	void bind();
	GLuint getProgram() { return m_program; };
	void update(const Transform& transform, const Camera& camera);
};
#endif
