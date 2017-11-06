//
// Created by roscale on 10/30/17.
//

#include "Component.hpp"

void Component::linkToGameObject(GameObject* gameObject) {
	this->gameObject = gameObject;
}
