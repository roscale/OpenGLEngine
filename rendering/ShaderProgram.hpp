//
// Created by roscale on 10/26/17.
//

#pragma once


#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class ShaderProgram {

//private:
public:
	unsigned int programID;
	unsigned int vertexShaderID;
	unsigned int fragmentShaderID;

	static unsigned int loadShader(const char* filename, unsigned int type);

public:
	virtual ~ShaderProgram() = default;

	void start();
	void stop();

	void bindAttribute(unsigned int attributeIndex, const char* variableName);

protected:
	ShaderProgram(const char* vertexShaderFilename, const char* fragmentShaderFilename);

	virtual void getAllUniformLocations() = 0;
	int getUniformLocation(const char* uniformName);

	void loadFloat(int location, float value);
	void loadVec3(int location, glm::vec3 vector);
	void loadBool(int location, bool value);
	void loadMat4(int location, glm::mat4 matrix);

	virtual void bindAttributes() = 0;
	void linkProgram();
};

