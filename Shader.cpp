#include "Shader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <glew.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include "Transform.h"

//Init static member
GLuint Shader::program = NULL;

//Getters and setters
std::string Shader::getFilePath() { return this->filePath; }
GLuint Shader::getShader() { return this->shader; }
GLuint* Shader::getUniforms() { return this->uniforms; }
GLenum Shader::getShaderType() { return this->shaderType; }
void Shader::setFilePath(std::string filePath) { this->filePath = filePath; }
void Shader::setShader(GLuint shader) { this->shader = shader; }
void Shader::setShaderType(GLenum shaderType) { this->shaderType = shaderType; }

void Shader::init()
{
	//Get program from OpenGL if not already existent
	if (Shader::program == NULL)
	{
		Shader::program = glCreateProgram();
	}

	//Load, create, & attach shader, bind position attribute location
	setShader(createShader(loadShader(getFilePath()), getShaderType()));
	glAttachShader(Shader::program, getShader());
	glBindAttribLocation(Shader::program, 0, "position");

	//Link program & error check
	glLinkProgram(Shader::program);
	checkShaderError(Shader::program, GL_LINK_STATUS, true);

	//Validate & error check
	glValidateProgram(Shader::program);
	checkShaderError(Shader::program, GL_VALIDATE_STATUS, true);
}

void Shader::bind() 
{
	//Bind the program (static variable in Shader class)
	glUseProgram(Shader::program);
}

void Shader::update(Transform& transform, Camera& camera)
{
	//Combine view projection matrix with the model/world matrix
	glm::mat4 mvp = camera.getViewProjection() * transform.getWorld();

	//Send our transformation and projection data to our shader program
	glUniformMatrix4fv(uniforms[TRANSFORM], 1, GL_FALSE, &mvp[0][0]);
}

Shader::Shader(std::string filePath, GLenum shaderType)
{
	//Set attributes given parameters
	setFilePath(filePath);
	setShaderType(shaderType);

	//Initialize shader
	init();
}

Shader::~Shader() 
{
	//Detach and delete shader & program
	glDetachShader(Shader::program, getShader());
	glDeleteShader(getShader());
	glDeleteProgram(Shader::program);
}