//
// Created by roscale on 10/30/17.
//

#pragma once

#include <string>
#include "../interfaces/IEvents.hpp"

class GameObject;

class Component : public IEvents {
	friend class GameObject;

public:
	GameObject* gameObject = nullptr;

	virtual std::string classStr() const = 0;
	virtual Component* clone() const = 0;

private:
	void linkToGameObject(GameObject* gameObject);
};

