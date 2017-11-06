//
// Created by roscale on 10/30/17.
//

#include <GLFW/glfw3.h>
#include <iostream>
#include "World.hpp"
#include "../rendering/DisplayManager.hpp"
#include "InputManager.hpp"

std::vector<GameObject*> World::gameObjects = std::vector<GameObject*>();

GameObject* World::instantiate(GameObject* prefab,
                               const glm::vec3& position,
                               const glm::vec3& rotation,
                               const glm::vec3& scale) {

	GameObject* instance = new GameObject(*prefab);
	instance->transform->position = position;
	instance->transform->rotation = rotation;
	instance->transform->scale = scale;
	gameObjects.push_back(instance);

	return instance;
}

void World::start() {
	for (const auto& gameObject : World::gameObjects) {
		for (const auto& component : gameObject->components) {
			component->onStart();
		}
	}
}

void World::update() {
	glfwPollEvents();

	for (const auto& gameObject : World::gameObjects) {
		for (const auto& component : gameObject->components) {
			component->onUpdate();
		}
	}
}

GameObject* World::find(std::string name) {
	for (const auto& gameObject : gameObjects) {
		if (gameObject->name == name) {
			return gameObject;
		}
	}
	return nullptr;
}

