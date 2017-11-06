//
// Created by roscale on 10/25/17.
//

#include <GL/glew.h>

#include <utility>
#include <fstream>
#include <iostream>
#include "Loader.hpp"

Model* Loader::loadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<unsigned int> indices) {
	unsigned int vaoID = createVAO();
	bindIndicesBuffer(indices);
	storeDataInAttributeList(0, std::move(positions), 3);
	storeDataInAttributeList(1, std::move(textureCoords), 2);
	storeDataInAttributeList(2, std::move(normals), 3);

	unbindVAO();

	return new Model(vaoID, static_cast<unsigned int>(indices.size()));
}

unsigned int Loader::createVAO() {
	unsigned int vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void Loader::storeDataInAttributeList(unsigned int attributeNumber, std::vector<float> data, int numberComponents) {
	unsigned int vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(
			attributeNumber, numberComponents, GL_FLOAT, GL_FALSE, 0, nullptr
	);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(std::vector<unsigned int> indices) {
	unsigned int vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Loader::unbindVAO() {
	glBindVertexArray(0);
}

unsigned int Loader::loadTexture(const char* filepath) {
	char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;

	std::ifstream file(filepath);
	if (!file.is_open()) {
		std::cerr << filepath << " image couldn't be opened\n";
		return 0;
	}

	file.read(header, 54);
	if ( header[0]!='B' || header[1]!='M' ){
		std::cerr << "Not a correct BMP file\n";
		return 0;
	}

	dataPos    = *(unsigned int*)&(header[0x0A]);
	imageSize  = *(unsigned int*)&(header[0x22]);
	width      = *(unsigned int*)&(header[0x12]);
	height     = *(unsigned int*)&(header[0x16]);

	if (imageSize==0)    imageSize = width*height*3;
	if (dataPos==0)      dataPos = 54;

	std::string data( (std::istreambuf_iterator<char>(file) ),
	                  (std::istreambuf_iterator<char>()    ) );
	file.close();

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	for (int c = 0; c < data.size() / 2; c += 1) {
		char temp = data[c];
		data[c] = data[data.size()-1-c];
		data[data.size()-1-c] = temp;
	}

//	std::cout << "size: " << data.size() << std::endl;
//	for (int c = 0; c < data.size(); c += 4) {
//		char temp = data[c];
//		data[c] = data[c+3];
//		data[c+3] = temp;
//	}





//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data.data());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());

//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	return textureID;
}

