//
// Created by roscale on 10/25/17.
//

#include "Model.hpp"

Model::Model(unsigned int vaoID, unsigned int vertexCount) {
	this->vaoID = vaoID;
	this->vertexCount = vertexCount;
}

unsigned int Model::getVaoID() const {
	return vaoID;
}

unsigned int Model::getVertexCount() const {
	return vertexCount;
}
