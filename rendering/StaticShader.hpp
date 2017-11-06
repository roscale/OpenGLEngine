//
// Created by roscale on 10/26/17.
//

#pragma once


#include "ShaderProgram.hpp"
#include "../prefabs/GameObject.hpp"

class StaticShader final : public ShaderProgram{
private:
	StaticShader(const char* vertexShaderFilename, const char* fragmentShaderFilename);

	int location_transformationMatrix;
	int location_viewMatrix;
	int location_projectionMatrix;
	int location_lightPosition;
	int location_lightColor;
	int location_shineDamper;
	int location_reflectivity;
	int location_skyColor;
	int location_fogDensity;
	int location_fogGradient;


public:
	static StaticShader createShaderProgram(const char* filename, const char* type);
	void loadTransformationMatrix(glm::mat4 matrix);
	void loadViewMatrix(glm::mat4 view);
	void loadProjectionMatrix(glm::mat4 projection);
	void loadLight(const GameObject* light);

	void loadShineVariables(float damper, float reflectivity);

	void loadSkyColor(glm::vec3 color);
	void loadFogVariables(float density, float gradient);

protected:
	void bindAttributes() override;

	void getAllUniformLocations() override;
};

