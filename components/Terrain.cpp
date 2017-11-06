//
// Created by roscale on 10/31/17.
//

#include <iostream>
#include "Terrain.hpp"
#include "../rendering/Loader.hpp"
#include "../util/util.hpp"

void Terrain::generateTerrain(unsigned int tilesX, unsigned int tilesY) {
	unsigned int VERTEX_COUNT = 128;
	if (highmap != nullptr) {
		VERTEX_COUNT = highmap->height;
	}

	std::cout << "vc: " << VERTEX_COUNT << std::endl;

	unsigned int count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<float> vertices;        vertices.resize(count * 3);
	std::vector<float> normals;         normals.resize(count * 3);
	std::vector<float> textureCoords;   textureCoords.resize(count*2);
	std::vector<unsigned int> indices;  indices.resize(6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1));

	int vertexPointer = 0;
	for (int i=0; i<VERTEX_COUNT; i++){
		for (int j=0; j<VERTEX_COUNT; j++){
			vertices[vertexPointer*3] = (float)j/((float)VERTEX_COUNT - 1) * width;

			float height = map(highmap->getPixelAt(j, i).r, 255, 0, 0, 5);
			vertices[vertexPointer*3+1] = height;

			vertices[vertexPointer*3+2] = (float)i/((float)VERTEX_COUNT - 1) * length;

			normals[vertexPointer*3] = 0;
			normals[vertexPointer*3+1] = 1;
			normals[vertexPointer*3+2] = 0;

			textureCoords[vertexPointer*2] = (float)j/VERTEX_COUNT*tilesX;
			textureCoords[vertexPointer*2+1] = (float)i/VERTEX_COUNT*tilesY;
			vertexPointer++;
		}
	}

	int pointer = 0;
	for (int gz=0; gz<VERTEX_COUNT-1; gz++) {
		for (int gx=0; gx<VERTEX_COUNT-1; gx++) {
			unsigned int topLeft = (gz*VERTEX_COUNT)+gx;
			unsigned int topRight = topLeft + 1;
			unsigned int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
			unsigned int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	std::cout << "size: " << vertices.size() << std::endl;
	model = Loader::loadToVAO(vertices, textureCoords, normals, indices);
}

std::string Terrain::classStr() const {
	return "Terrain";
}

Component* Terrain::clone() const {
	return new Terrain(*this);
}
