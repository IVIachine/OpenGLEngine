#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "Transform.h"
#include "Camera.h"

class Shader : public Trackable
{
public:
	Shader();
	Shader(const Shader& copy);
	~Shader();

	void bind();
	GLuint getProgram() { return m_program; };
	void update(const Transform& transform, const Camera& camera);

private:
	static const size_t NUM_SHADERS = 2;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];

	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	GLuint m_uniforms[NUM_UNIFORMS];

	Shader(const std::string& fileName);

	friend class ResourceManager;
};
#endif
