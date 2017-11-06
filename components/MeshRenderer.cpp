//
// Created by roscale on 10/30/17.
//

#include "MeshRenderer.hpp"

std::string MeshRenderer::classStr() const {
	return "MeshRenderer";
}

Component* MeshRenderer::clone() const {
	return new MeshRenderer(*this);
}
