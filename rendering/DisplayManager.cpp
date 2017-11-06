//
// Created by roscale on 10/24/17.
//

#include <iostream>
#include <GL/glew.h>
#include "DisplayManager.hpp"
#include "../core/Time.hpp"

int DisplayManager::width = 0;
int DisplayManager::height = 0;
GLFWwindow* DisplayManager::window = nullptr;

void DisplayManager::createDisplay(int width, int height, const char* title) {
	DisplayManager::width = width;
	DisplayManager::height = height;

	/* Initialize the library */
	if (!glfwInit()) {
		std::cerr << "Could not initialize GLFW\n";
	}

	/* Create a windowed mode window and its OpenGL context */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	DisplayManager::window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (!window)
	{
		std::cerr << "Could not create window\n";
		glfwTerminate();
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Initialize GLEW */
	glewExperimental = GL_TRUE;

	int err;
	err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "Could not initialize GLEW\n" << err;
		glfwTerminate();
	}

	glEnable(GL_DEPTH_TEST);
}

void DisplayManager::closeDisplay() {
	glfwTerminate();
}

void DisplayManager::updateDisplay() {
	/* Swap front and back buffers */
	glfwSwapBuffers(DisplayManager::window);
}