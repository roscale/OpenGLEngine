//
// Created by roscale on 11/3/17.
//

#include <GLFW/glfw3.h>
#include "Time.hpp"

double Time::lastFrameTime = 0;
float Time::deltaTime = 0;

double Time::getCurrentTime() {
	return glfwGetTime();
}

void Time::init() {
	lastFrameTime = getCurrentTime();
}

void Time::update() {
	double currentTime = getCurrentTime();
	deltaTime = static_cast<float>(currentTime - lastFrameTime);
	lastFrameTime = currentTime;
}
