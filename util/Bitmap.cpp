//
// Created by roscale on 11/4/17.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <glm/vec4.hpp>
#include "Bitmap.hpp"
#include "util.hpp"

Bitmap::Bitmap(const std::string& filepath) : filepath(filepath) {
	std::ifstream file(filepath);
	if (!file.is_open()) {
		throw FileNotFound(filepath + " image couldn't be opened.");
	}

	auto fileBytes = std::vector<byte>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

	if (fileBytes[0]!='B' || fileBytes[1]!='M'){
		std::cerr << "Not a correct BMP file\n";
	}

	width = *(unsigned int*)&(fileBytes[0x12]);
	height = *(unsigned int*)&(fileBytes[0x16]);
	colorDepth = *(unsigned short*)&(fileBytes[0x1C]);

	unsigned int pixelArrayOffset = *(unsigned int*)&(fileBytes[0x0A]);

	pixelArray = std::vector<byte>(&(fileBytes[pixelArrayOffset]), &(fileBytes[pixelArrayOffset]) + (width * height * 4));
	std::cout << (int)pixelArray[0] << std::endl;

	file.close();
}

glm::vec4 Bitmap::getPixelAt(int x, int y) {
	glm::vec4 pixel;
	int stride = colorDepth / 8;
	y = height-1 - y;

	if (colorDepth == 32) {
		pixel.a = pixelArray[stride * (width * y + x)];
		pixel.r = pixelArray[stride * (width * y + x) + 1];
		pixel.g = pixelArray[stride * (width * y + x) + 2];
		pixel.b = pixelArray[stride * (width * y + x) + 3];
	} else if (colorDepth == 8) {
		pixel.a = 255;
		pixel.r = pixelArray[stride * (width * y + x)];
		pixel.g = pixel.r;
		pixel.b = pixel.r;
	}

	return pixel;
}
