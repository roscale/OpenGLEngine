//
// Created by roscale on 10/30/17.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Transform.hpp"

void Transform::translate(float dx, float dy, float dz) {
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

void Transform::translate(glm::vec3 vec) {
	translate(vec.x, vec.y, vec.z);
}

void Transform::rotate(float dx, float dy, float dz) {
	rotation.x += dx;
	rotation.y += dy;
	rotation.z += dz;
}

void Transform::rotate(glm::vec3 vec) {
	rotate(vec.x, vec.y, vec.z);
}

glm::mat4 Transform::getTransformationMatrix() const {
	glm::mat4 matrix = glm::translate(glm::mat4(1.0f), position);

	matrix = glm::rotate(matrix, rotation.x, glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, rotation.y, glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, rotation.z, glm::vec3(0, 0, 1));

	matrix = glm::scale(matrix, scale);

	return matrix;
}

std::string Transform::classStr() const {
	return "Transform";
}

Component* Transform::clone() const {
	return new Transform(*this);
}
