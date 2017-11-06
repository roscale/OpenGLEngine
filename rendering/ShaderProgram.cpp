//
// Created by roscale on 10/26/17.
//

#include <fstream>
#include <iostream>
#include "ShaderProgram.hpp"
#include "../util/util.hpp"
#include <glm/glm.hpp>

unsigned int ShaderProgram::loadShader(const char* filename, unsigned int type) {
	std::string fileStr;

	fileStr = util::readFile(filename);

	unsigned int shaderID = glCreateShader(type);

	const char *c_str = fileStr.c_str();
	glShaderSource(shaderID, 1, &c_str, nullptr);
	glCompileShader(shaderID);

	int compileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		int infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		auto* infoBuffer = new char[infoLogLength+1];

		glGetShaderInfoLog(shaderID, infoLogLength, &infoLogLength, infoBuffer);
		std::cerr << "Error compiling '" << filename << "': " << infoBuffer;
		delete[] infoBuffer;
	}

	return shaderID;
}

ShaderProgram::ShaderProgram(const char* vertexShaderFilename, const char* fragmentShaderFilename) {
	vertexShaderID = ShaderProgram::loadShader(vertexShaderFilename, GL_VERTEX_SHADER);
	fragmentShaderID = ShaderProgram::loadShader(fragmentShaderFilename, GL_FRAGMENT_SHADER);

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
}

void ShaderProgram::start() {
	glUseProgram(programID);
}

void ShaderProgram::stop() {
	glUseProgram(0);
}

void ShaderProgram::bindAttribute(unsigned int attributeIndex, const char* variableName) {
	glBindAttribLocation(programID, attributeIndex, variableName);
}

void ShaderProgram::linkProgram() {
	glLinkProgram(programID);
	glValidateProgram(programID);

	getAllUniformLocations();
}

int ShaderProgram::getUniformLocation(const char* uniformName) {
	return glGetUniformLocation(programID, uniformName);
}

void ShaderProgram::loadFloat(int location, float value) {
	glUniform1f(location, value);
}

void ShaderProgram::loadVec3(int location, glm::vec3 vector) {
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::loadBool(int location, bool value) {
	glUniform1i(location, value);
}

void ShaderProgram::loadMat4(int location, glm::mat4 matrix) {
	float buffer[16];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			buffer[4*i + j] = matrix[i][j];
		}
	}

	glUniformMatrix4fv(location, 1, GL_FALSE, buffer);
}

