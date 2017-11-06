//
// Created by roscale on 10/30/17.
//

#pragma once


#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Component.hpp"

class Transform : public Component {
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	void translate(float dx, float dy, float dz);
	void translate(glm::vec3 vec);
	void rotate(float dx, float dy, float dz);
	void rotate(glm::vec3 vec);

	glm::mat4 getTransformationMatrix() const;

	std::string classStr() const override;
	Component* clone() const override;
};

