//
// Created by roscale on 10/31/17.
//

#pragma once


#include "Component.hpp"
#include "../models/Model.hpp"
#include "../rendering/Texture.hpp"
#include "../rendering/ShaderProgram.hpp"
#include "../util/Bitmap.hpp"

class Terrain : public Component {
public:
	Model* model = nullptr;
	Texture* texture = nullptr;
	ShaderProgram* program = nullptr;
	Bitmap* highmap = nullptr;

	float width = 80.0f;
	float length = 80.0f;

	void generateTerrain(unsigned int tilesX, unsigned int tilesY);

	std::string classStr() const override;
	Component* clone() const override;
};

