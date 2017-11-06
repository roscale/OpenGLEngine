//
// Created by roscale on 10/30/17.
//

#pragma once


#include <vector>
#include "../prefabs/GameObject.hpp"

class World {
public:
	World() = delete;
	static std::vector<GameObject*> gameObjects;

	static GameObject* instantiate(GameObject* prefab,
	                               const glm::vec3& position = {0, 0, 0},
	                               const glm::vec3& rotation = {0, 0, 0},
	                               const glm::vec3& scale = {1, 1, 1});

	static GameObject* find(std::string name);

	static void start();
	static void update();
};

