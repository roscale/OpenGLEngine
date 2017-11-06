//
// Created by roscale on 10/30/17.
//

#include "GameObject.hpp"

void GameObject::addComponent(Component* component) {
	components.push_back(component);
	component->linkToGameObject(this);
}

GameObject::GameObject() {
	transform = new Transform();
	addComponent(transform);
}

GameObject::GameObject(const GameObject& other) {
	name = other.name;

	transform = new Transform(*other.transform);

	for (const auto& component : other.components) {
		Component* clonedComponent = component->clone();
		clonedComponent->linkToGameObject(this);
		components.push_back(clonedComponent);
	}
}

Component* GameObject::getComponent(const std::string& classStr) const {
	for (const auto& component : components) {
		if (component->classStr() == classStr) {
			return component;
		}
	}
	return nullptr;
}
