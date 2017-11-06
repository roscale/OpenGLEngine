//
// Created by roscale on 10/30/17.
//

#include "Mesh.hpp"

void Mesh::useModel(Model* model) {
	this->model = model;
}

std::string Mesh::classStr() const {
	return "Mesh";
}

Component* Mesh::clone() const {
	return new Mesh(*this);
}
