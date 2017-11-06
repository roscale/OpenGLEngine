//
// Created by roscale on 11/4/17.
//

#pragma once


#include <vector>
#include <glm/vec3.hpp>

using byte = unsigned char;

class Bitmap {
public:
	explicit Bitmap(const std::string& filepath);

	std::string filepath;

	unsigned int width;
	unsigned int height;
	unsigned short colorDepth;

	std::vector<byte> pixelArray;

	glm::vec4 getPixelAt(int x, int y);
};

