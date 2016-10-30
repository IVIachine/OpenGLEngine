#include "Shader.h"
#include <fstream>
#include <iostream>
#include "Graphics.h"

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage);
static std::string loadShader(const std::string & fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);


Shader::Shader()
{
}

Shader::Shader(const std::string & fileName)
{
	m_program = glCreateProgram(); //Create a program
	m_shaders[0] = CreateShader(loadShader(fileName + ".verts"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(loadShader(fileName + ".frags"), GL_FRAGMENT_SHADER);

	for (size_t i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position"); //Tells opengl where to read in shader program
	glBindAttribLocation(m_program, 1, "texCoord");

	glLinkProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "Error: Program failed to link: ");

	glValidateProgram(m_program);
	checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program invalid: "); //Check if everything links and validates properly

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform"); //Give shader access to transform uniform
}

Shader::Shader(const Shader & copy)
{
	m_program = copy.m_program;
	
	for (size_t i = 0; i < NUM_SHADERS; i++)
	{
		m_shaders[i] = copy.m_shaders[i];
	}
}

Shader::~Shader()
{
	for (size_t i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);			//Detach and delete all shaders
	}
	glDeleteProgram(m_program);  //Delete the program
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Error with shader creation" << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str(); //Create and init glstring
	shaderSourceStringLengths[0] = text.length(); //Store the string and length

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: shader compile failure: ");

	return shader;
}

static std::string loadShader(const std::string & fileName)
{
	std::ifstream file;
	file.open((fileName.c_str()));

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			std::getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

void Shader::bind()
{
	glUseProgram(m_program);
}

void Shader::update(const Transform & transform, const Camera& camera)
{
	glDepthMask(GL_TRUE);
	Matrix model = camera.getViewProjection() * transform.getModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]); //Updates a uniform ** MAY NEED TO REPLACE FALSE WITH TRANSPOSE
		//fv = float values
}
