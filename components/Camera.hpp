//
// Created by roscale on 10/30/17.
//

#pragma once


#include "Component.hpp"
#include <glm/vec3.hpp>

class Camera : public Component {
//public:
//	enum Mode {
//		FIRST_PERSON,
//		THIRD_PERSON,
//	};

public:
	static Camera* mainCamera;

public:
	float FOV = 70.0f;
	float NEAR_PLANE = 0.1f;
	float FAR_PLANE = 100.0f;

	glm::vec4 backgroundColor = {0, 0, 0, 1};

	float fogDensity = 0.012f;
	float fogGradient = 10.0f;

	glm::mat4 projectionMatrix;

public:
	Camera();

	void setMainCamera();

	glm::mat4 getViewMatrix();
	void createProjectionMatrix();

	std::string classStr() const override;
	Component* clone() const override;

	void onStart() override;
};

