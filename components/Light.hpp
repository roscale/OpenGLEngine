//
// Created by roscale on 10/30/17.
//

#pragma once


#include <glm/vec3.hpp>
#include "Component.hpp"

class Light : public Component {
public:
	glm::vec3 color;

	std::string classStr() const override;
	Component* clone() const override;
};

