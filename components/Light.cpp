//
// Created by roscale on 10/30/17.
//

#include "Light.hpp"

std::string Light::classStr() const {
	return "Light";
}

Component* Light::clone() const {
	return new Light(*this);
}

