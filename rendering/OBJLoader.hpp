//
// Created by roscale on 10/30/17.
//

#pragma once


#include "../models/Model.hpp"
#include "Loader.hpp"

class OBJLoader {
public:
	static Model* loadObjModel(const char* filename);
};

