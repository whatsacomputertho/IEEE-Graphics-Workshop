#include <stdio.h>
#include <glew.h>
#include <SDL.h>
#include <glm.hpp>
#include "Window.h"
#include "Shader.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Transform.h"

int main(int argc, char** argv)
{
	Window window = Window("IEEE Graphics Workshop", 640, 480);

	Shader vertexShader = Shader("./shaders/VertexShader.vs", GL_VERTEX_SHADER);
	Shader fragmentShader = Shader("./shaders/FragmentShader.fs", GL_FRAGMENT_SHADER);
	vertexShader.getUniforms()[vertexShader.TRANSFORM] = (glGetUniformLocation(Shader::program, "transform"));

	Vertex vertex[6] =
	{
		Vertex(glm::vec3(0.5f, -0.5f, 0.0f)),
		Vertex(glm::vec3(0.0f, 0.5f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.0f)),

		Vertex(glm::vec3(0.5f, -0.5f, 0.5f)),
		Vertex(glm::vec3(0.0f, 0.5f, 0.5f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f))
	};

	Mesh mesh = Mesh(vertex, sizeof(vertex)/sizeof(vertex[0]));

	Transform transform = Transform();

	float transformCounter = 0.0f;

	while (!window.isClosed()) 
	{
		glClearColor(0.09f, 0.13f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		transform.setRotation(glm::vec3(transform.getRotation().x, transformCounter, transform.getRotation().z));

		fragmentShader.bind();
		vertexShader.update(transform);

		mesh.draw();

		window.update();

		transformCounter += 0.0006f;
	}

	return 0;
}