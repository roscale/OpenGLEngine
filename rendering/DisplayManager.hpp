//
// Created by roscale on 10/24/17.
//

#pragma once


#include <GLFW/glfw3.h>
#include <memory>

class DisplayManager {
public:
	DisplayManager() = delete;

	static int width;
	static int height;

	static GLFWwindow* window;

	static void createDisplay(int width, int height, const char* title);
	static void updateDisplay();
	static void closeDisplay();
};

