//
// Created by roscale on 10/30/17.
//

#pragma once


#include "Component.hpp"
#include "../models/Model.hpp"

class Mesh : public Component {
public:
	Model* model;

	void useModel(Model* model);

	std::string classStr() const override;
	Component* clone() const override;
};

