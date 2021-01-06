#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <glew.h>
#include "Transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader(std::string filePath, GLenum shaderType);
	~Shader();
	void bind();
	void update(Transform& transform, Camera& camera);
	static GLuint program;
	static Camera camera;
	std::string getFilePath();
	GLuint getShader();
	GLuint* getUniforms();
	GLenum getShaderType();
	void setFilePath(std::string filePath);
	void setShader(GLuint shader);
	void setShaderType(GLenum shaderType);
	enum
	{
		TRANSFORM,
		NUM_UNIFORMS
	};

private:
	std::string filePath;
	GLuint shader;
	GLuint uniforms[NUM_UNIFORMS];
	GLenum shaderType;
	void init();
	static std::string loadShader(std::string filePath)
	{
		//Initialize a file input stream given a file path
		std::ifstream file;
		file.open(filePath.c_str());

		//Initialize two strings, one to read line by line, and the other to which to append file contents
		std::string output;
		std::string line;

		//Check if file is open, if so, loop through it and get its contents
		if (file.is_open())
		{
			while (file.good())
			{
				getline(file, line);
				output.append(line + '\n');
			}
		}
		else 
		{
			std::cerr << "Unable to load shader: " << filePath << std::endl;
		}

		//Return program text
		return output;
	}
	static void checkShaderError(GLuint shader, GLuint flag, bool isProgram) 
	{
		//Initialize flag & empty error text
		GLint success = 0;
		GLchar error[1024] = { 0 };

		//Check if shader or if program, run different functions accordingly
		if (isProgram)
			glGetProgramiv(shader, flag, &success);
		else
			glGetShaderiv(shader, flag, &success);

		//Check for success
		if (success == GL_FALSE) 
		{
			//Check if shader or if program, run different functions accordingly
			if (isProgram)
				glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			else
				glGetShaderInfoLog(shader, sizeof(error), NULL, error);

			//Print error message
			std::cerr << error << std::endl;
		}
	}
	static GLuint createShader(std::string text, GLenum shaderType)
	{
		//Create shader
		GLuint shader = glCreateShader(shaderType);

		//Error check
		if (shader == 0)
			std::cerr << "Shader creation failed" << std::endl;

		//Convert source code to useful type
		const GLchar* shaderSourceStrings[1] = { text.c_str() };
		GLint shaderSourceStringLengths[1] = { text.length() };

		//Compile
		glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
		glCompileShader(shader);

		//Error check
		checkShaderError(shader, GL_COMPILE_STATUS, false);

		//Return compiled shader
		return shader;
	}
};