#include <stdio.h>
#include <glew.h>
#include <SDL.h>
#include <glm.hpp>
#include "Window.h"
#include "Shader.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"

int main(int argc, char** argv)
{
	//Instantiate a window with a title, width, and height
	Window window = Window("IEEE Graphics Workshop", 640, 480);

	//Instantiate vertex and fragment shaders with their respective filepaths and types
	Shader vertexShader = Shader("./shaders/VertexShader.vs", GL_VERTEX_SHADER);
	Shader fragmentShader = Shader("./shaders/FragmentShader.fs", GL_FRAGMENT_SHADER);

	//Instantiate a camera with a position vector, a field of view angle, the aspect ratio (width/height), the near depth threshold, and the far depth threshold
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, -3.0f), 70.0f, ((float)window.getWidth())/((float)window.getHeight()), 0.01f, 1000.0f);

	//Get uniform variable address from our vertex shader program & add to vertex shader object
	vertexShader.getUniforms()[vertexShader.TRANSFORM_RESOLUTION] = (glGetUniformLocation(Shader::program, "transform"));
	fragmentShader.getUniforms()[fragmentShader.TRANSFORM_RESOLUTION] = (glGetUniformLocation(Shader::program, "resolution"));

	//Hardcode a vertex array specifying two triangles offset by 0.5 units in the z direction
	Vertex vertex[6] =
	{
		Vertex(glm::vec3(0.5f, -0.5f, 0.0f)),
		Vertex(glm::vec3(0.0f, 0.5f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.0f)),

		Vertex(glm::vec3(0.5f, -0.5f, 0.5f)),
		Vertex(glm::vec3(0.0f, 0.5f, 0.5f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f))
	};


	//Instantiate mesh using vertex data above & the size of a given vertex
	Mesh mesh = Mesh(vertex, sizeof(vertex)/sizeof(vertex[0]));

	//Instantiate a transform to use on our mesh
	Transform transform = Transform();

	//Initialize a counter for our transform (using a float because we can slow down or speed up transformations using smaller or larger incrementations respectively)
	float transformCounter = 0.0f;

	//Main loop
	while (!window.isClosed()) 
	{
		//Clear the screen (floats below specify the clear color, I opted to use dark blue)
		glClearColor(0.09f, 0.13f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Rotate the mesh we created around its y axis
		transform.setRotation(glm::vec3(transform.getRotation().x, transformCounter, transform.getRotation().z));

		//Bind our shader program to our shader files (only need to run once per loop for both shaders)
		fragmentShader.bind();

		//Update our vertex shader data using our transform operations and our camera for projection
		vertexShader.update(transform, camera);

		//Actually draw the mesh to the screen
		mesh.draw();

		//Update our fragment shader data using our window resolution
		fragmentShader.update(glm::vec2((float)window.getWidth(), (float)window.getHeight()));

		//Swap buffers and input poll
		window.update(camera);

		//Increment our counter -- make smaller for fast processors, larger for slow processors
		transformCounter += 0.0006f;
	}

	//int main() return statement
	return 0;
}