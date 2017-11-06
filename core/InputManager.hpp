//
// Created by roscale on 11/2/17.
//

#pragma once


#include <GLFW/glfw3.h>

class InputManager {
private:
	static double oldxpos, oldypos;

public:
	static void init();

	static void key(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void mouseMotion(GLFWwindow* window, double xpos, double ypos);
	static void mouseEnter(GLFWwindow* window, int entered);
	static void mouseButton(GLFWwindow* window, int button, int action, int mods);
	static void mouseScroll(GLFWwindow* window, double xoffset, double yoffset);
};

