//
// Created by roscale on 10/26/17.
//

#include <iostream>
#include "ShaderProgram.hpp"
#include "StaticShader.hpp"
#include "../components/Light.hpp"

StaticShader::StaticShader(const char* vertexShaderFilename, const char* fragmentShaderFilename)
		: ShaderProgram(vertexShaderFilename, fragmentShaderFilename) {

}

void StaticShader::bindAttributes() {
	ShaderProgram::bindAttribute(0, "position");
	ShaderProgram::bindAttribute(1, "textureCoords");
	ShaderProgram::bindAttribute(2, "normal");
}

StaticShader StaticShader::createShaderProgram(const char* filename, const char* type) {
	StaticShader program(filename, type);
	program.bindAttributes();
	program.linkProgram();
	return program;
}

void StaticShader::getAllUniformLocations() {
	location_transformationMatrix = ShaderProgram::getUniformLocation("transformationMatrix");
	location_viewMatrix = ShaderProgram::getUniformLocation("viewMatrix");
	location_projectionMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
	location_lightPosition = ShaderProgram::getUniformLocation("lightPosition");
	location_lightColor = ShaderProgram::getUniformLocation("lightColor");
	location_shineDamper = ShaderProgram::getUniformLocation("shineDamper");
	location_reflectivity = ShaderProgram::getUniformLocation("reflectivity");
	location_skyColor = ShaderProgram::getUniformLocation("skyColor");
	location_fogDensity = ShaderProgram::getUniformLocation("fogDensity");
	location_fogGradient = ShaderProgram::getUniformLocation("fogGradient");
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
	ShaderProgram::loadMat4(location_transformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 projection) {
	ShaderProgram::loadMat4(location_projectionMatrix, projection);
}

void StaticShader::loadViewMatrix(glm::mat4 view) {
	ShaderProgram::loadMat4(location_viewMatrix, view);
}

void StaticShader::loadLight(const GameObject* light) {
	Light* lightComponent = reinterpret_cast<Light*>(light->getComponent("Light"));
	if (lightComponent == nullptr)
		return;

	loadVec3(location_lightPosition, light->transform->position);
	loadVec3(location_lightColor, lightComponent->color);
}

void StaticShader::loadShineVariables(float damper, float reflectivity) {
	loadFloat(location_shineDamper, damper);
	loadFloat(location_reflectivity, reflectivity);
}

void StaticShader::loadSkyColor(glm::vec3 color) {
	loadVec3(location_skyColor, color);
}

void StaticShader::loadFogVariables(float density, float gradient) {
	loadFloat(location_fogDensity, density);
	loadFloat(location_fogGradient, gradient);
}
