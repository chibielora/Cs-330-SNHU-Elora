#include <application.h>
#include <types.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

Application::Application(
	std::string WindowTitle, 
	int width, 
	int height
) : _applicationName{ WindowTitle }, 
	_width{ width }, 
	_height{ height } {}

void Application::Run() {
	// Open the window
	if (!openWindow()) {
		return;
	}

	_running = true;

	// Rearrange the elements in the window
	rearrange();

	// Run app
	while (_running){
		if (glfwWindowShouldClose(_window)) {
			_running = true;
			break;
		}

		// Call function to update triangles
		update();
		// Call function to render triangles
		draw();

	}

	glfwTerminate();
}

bool Application::openWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(800, 600, "Module 2 | Elora Newcomb - CS-330", nullptr, nullptr);

	if (!_window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(_window);

	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	return true;
}

void Application::rearrange() {
		// Inputs for the Vertex shaders // Alpha not accessible
		auto vertexSource = R"(#version 330 core
		layout (location = 0) in vec3 position;
		layout (location = 1) in vec3 color;
		layout (location = 2) in vec3 normal;
		layout (location = 3) in vec2 uv;

		out vec4 vertexColor;

		uniform mat4 view;
		uniform mat4 projection;
		uniform mat4 model;
		
		void main()	{
			gl_Position = projection * view * model * vec4(position, 1);
			vertexColor = vec4(color, 1.f); 
		}
		)";

		// Output for Fragment Shader
		const std::string fragmentSource = R"(#version 330 core
		out vec4 FragColor;
		in vec4 vertexColor;
		void main()	{
			FragColor = vertexColor;
		}
		)";

		_meshes.emplace_back(TridimensionalShapes::cubeVertices, TridimensionalShapes::cubeElements);
		_shader = Shader(vertexSource, fragmentSource);
}

bool Application::update() {
	return false;
}

bool Application::draw() {
	// Clear the screen with specific color
	glClearColor(.0f, .3f, .3f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Camera matrix to move objects in the plane
	glm::mat4 view = glm::lookAt(glm::vec3(.0f, 1.f, -3.f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	// Perspective Camera
	// Matrix : 75° Field of View, W/H ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 projection = glm::perspective(glm::radians(75.f), (float)_width / (float)_height, .1f, 100.f);

	_shader.Bind();
	_shader.SetMat4("projection", projection);
	_shader.SetMat4("view", view);

	for (auto& mesh : _meshes) {
		mesh.Transform = glm::rotate(mesh.Transform, glm::radians(.01f), glm::vec3(0, 1, 0));
		mesh.Transform = glm::rotate(mesh.Transform, glm::radians(.01f), glm::vec3(0, 1, 0));
		_shader.SetMat4("model", mesh.Transform);
		mesh.Draw();
	}


	glfwSwapBuffers(_window);
	glfwPollEvents();

	return false;
}