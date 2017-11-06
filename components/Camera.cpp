//
// Created by roscale on 10/30/17.
//

#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.hpp"
#include "../rendering/DisplayManager.hpp"
#include "../prefabs/GameObject.hpp"

Camera* Camera::mainCamera = nullptr;

Camera::Camera() {
	createProjectionMatrix();
}

glm::mat4 Camera::getViewMatrix() {
	glm::mat4 matrix(1.0f);

	matrix = glm::rotate(matrix, -(gameObject->transform->rotation.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, -(gameObject->transform->rotation.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, -(gameObject->transform->rotation.z), glm::vec3(0, 0, 1));

	matrix = glm::translate(matrix, -(gameObject->transform->position));

	return matrix;
}

void Camera::createProjectionMatrix() {
	projectionMatrix = glm::perspective(glm::radians(FOV), (float)8.0f / 6.0f, NEAR_PLANE, FAR_PLANE);
}

void Camera::setMainCamera() {
	Camera::mainCamera = this;
}

void Camera::onStart() {
	if (Camera::mainCamera == nullptr) {
		setMainCamera();
	}
}

std::string Camera::classStr() const {
	return "Camera";
}

Component* Camera::clone() const {
	return new Camera(*this);
}