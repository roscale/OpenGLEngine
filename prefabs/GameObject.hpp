//
// Created by roscale on 10/30/17.
//

#pragma once


#include <vector>
#include "../components/Component.hpp"
#include "../components/Transform.hpp"
#include "../components/Mesh.hpp"

class GameObject {
public:
	std::string name = "Default";

	std::vector<Component*> components;
	Transform* transform;

	void addComponent(Component* component);
	Component* getComponent(const std::string& classStr) const;

public:
	GameObject();
	GameObject(const GameObject& other);
};