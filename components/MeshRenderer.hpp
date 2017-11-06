//
// Created by roscale on 10/30/17.
//

#pragma once


#include "Component.hpp"
#include "../rendering/Texture.hpp"
#include "../rendering/StaticShader.hpp"

class MeshRenderer : public Component {
public:
	Texture* texture = nullptr;
	StaticShader* shaderProgram = nullptr;

	std::string classStr() const override;
	Component* clone() const override;
};

