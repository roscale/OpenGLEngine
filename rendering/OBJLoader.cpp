//
// Created by roscale on 10/30/17.
//

#include <fstream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include "OBJLoader.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


Model* OBJLoader::loadObjModel(const char* filename) {
	std::ifstream file(filename, std::ios::in);

	std::string fileStr;
	if(!file.is_open()) {
		std::cerr << "Could not open file " << filename << "\n";
		return nullptr;
	}

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> normals;

	std::vector<unsigned int> indices;
	std::vector<float> ordered_vertices;
	std::vector<float> ordered_TextureCoords;
	std::vector<float> ordered_normals;

	std::string line;
	while(getline(file, line)) {
		if (boost::starts_with(line, "#") ||
		    boost::starts_with(line, "o") ||
		    boost::starts_with(line, "s") ||
		    boost::starts_with(line, "mtllib") ||
		    boost::starts_with(line, "use") ||
		    boost::starts_with(line, "g")) continue;

		std::vector<std::string> tokens;
		boost::split(tokens, line, [](char c) { return c == ' '; });

		if (tokens[0] == "v") {
			vertices.emplace_back(
					boost::lexical_cast<float>(tokens[1]),
					boost::lexical_cast<float>(tokens[2]),
					boost::lexical_cast<float>(tokens[3])
			);
		} else if (tokens[0] == "vt") {
			textureCoords.emplace_back(
					boost::lexical_cast<float>(tokens[1]),
					boost::lexical_cast<float>(tokens[2])
			);
		} else if (tokens[0] == "vn") {
			normals.emplace_back(
					boost::lexical_cast<float>(tokens[1]),
					boost::lexical_cast<float>(tokens[2]),
					boost::lexical_cast<float>(tokens[3])
			);
		} else if (tokens[0] == "f") {
			ordered_TextureCoords.resize(vertices.size() * 2);
			ordered_normals.resize(vertices.size() * 3);
			break;
		}
	}

	auto processVertex = [&](std::string vertexToken) -> void {
		std::vector<std::string> vertexData;
		boost::split(vertexData, vertexToken, [](char c) { return c == '/'; });

		unsigned int currentVertexPointer = boost::lexical_cast<unsigned int>(vertexData[0]) - 1;
		indices.push_back(currentVertexPointer);

		int textureCoordIndex = boost::lexical_cast<int>(vertexData[1]) - 1;
		ordered_TextureCoords[2*currentVertexPointer] = textureCoords[textureCoordIndex].x;
		ordered_TextureCoords[2*currentVertexPointer+1] = textureCoords[textureCoordIndex].y;

		int normalIndex = boost::lexical_cast<int>(vertexData[2]) - 1;

		ordered_normals[3*currentVertexPointer] = normals[normalIndex].x;
		ordered_normals[3*currentVertexPointer+1] = normals[normalIndex].y;
		ordered_normals[3*currentVertexPointer+2] = normals[normalIndex].z;
	};

	do {
		if (!boost::starts_with(line, "f "))
			continue;

		std::vector<std::string> tokens;
		boost::split(tokens, line, [](char c) { return c == ' '; });

		processVertex(tokens[1]);
		processVertex(tokens[2]);
		processVertex(tokens[3]);

	} while(getline(file, line));

	for (const auto& vertex : vertices) {
		ordered_vertices.push_back(vertex.x);
		ordered_vertices.push_back(vertex.y);
		ordered_vertices.push_back(vertex.z);
	}

	file.close();

//	for (const auto& da : ordered_normals) {
//		std::cout << da << '\n';
//	}

	return Loader::loadToVAO(ordered_vertices, ordered_TextureCoords, ordered_normals, indices);
}
