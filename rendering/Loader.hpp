//
// Created by roscale on 10/25/17.
//

#pragma once


#include <vector>
#include "../models/Model.hpp"

class Loader {
public:
	static Model* loadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<unsigned int> indices);
	static unsigned int loadTexture(const char* filepath);

private:
	static std::vector<unsigned int> vaos;
	static std::vector<unsigned int> vbos;

	static unsigned int createVAO();
	static void storeDataInAttributeList(unsigned int attributeNumber, std::vector<float> data, int numberComponents);
	static void bindIndicesBuffer(std::vector<unsigned int> indices);
	static void unbindVAO();
//	void cleanUp();
};

