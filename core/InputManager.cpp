//
// Created by roscale on 11/2/17.
//

#include "InputManager.hpp"
#include "../rendering/DisplayManager.hpp"
#include "World.hpp"

double InputManager::oldxpos = 0;
double InputManager::oldypos = 0;

void InputManager::init() {
	glfwSetKeyCallback(DisplayManager::window, InputManager::key);
	glfwSetCursorPosCallback(DisplayManager::window, InputManager::mouseMotion);
	glfwSetCursorEnterCallback(DisplayManager::window, InputManager::mouseEnter);
	glfwSetMouseButtonCallback(DisplayManager::window, InputManager::mouseButton);
	glfwSetScrollCallback(DisplayManager::window, InputManager::mouseScroll);

	glfwSetCursorPos(DisplayManager::window, 0, 0);
}

void InputManager::key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	for (const auto& gameObject : World::gameObjects)
		for (const auto& component : gameObject->components) {
			component->onKey(key, scancode, action, mods);
		}
}

void InputManager::mouseMotion(GLFWwindow* window, double xpos, double ypos) {
	double xrel = xpos - oldxpos;
	double yrel = ypos - oldypos;

	for (const auto& gameObject : World::gameObjects)
		for (const auto& component : gameObject->components) {
			component->onMouseMotion(xpos, ypos, xrel, yrel);
		}

	oldxpos = xpos;
	oldypos = ypos;
}

void InputManager::mouseEnter(GLFWwindow* window, int entered) {
	for (const auto& gameObject : World::gameObjects)
		for (const auto& component : gameObject->components) {
			component->onMouseEnter((bool)entered);
		}
}

void InputManager::mouseButton(GLFWwindow* window, int button, int action, int mods) {
	for (const auto& gameObject : World::gameObjects)
		for (const auto& component : gameObject->components) {
			component->onMouseButton(button, action, mods);
		}
}

void InputManager::mouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
	for (const auto& gameObject : World::gameObjects)
		for (const auto& component : gameObject->components) {
			component->onMouseScroll(xoffset, yoffset);
		}
}
