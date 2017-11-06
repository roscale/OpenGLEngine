//
// Created by roscale on 10/25/17.
//

#include <GL/glew.h>
#include <iostream>
#include "Renderer.hpp"
#include "../components/MeshRenderer.hpp"
#include "../components/Terrain.hpp"

Renderer::Renderer() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Renderer::prepare() {
	glm::vec4 backgroundColor = Camera::mainCamera->backgroundColor;
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(GameObject* go, StaticShader& program, const GameObject* light) {
	auto* mesh = reinterpret_cast<Mesh*>(go->getComponent("Mesh"));
	auto* terrain = reinterpret_cast<Terrain*>(go->getComponent("Terrain"));

	if (mesh != nullptr) {
		auto* meshRenderer = reinterpret_cast<MeshRenderer*>(go->getComponent("MeshRenderer"));

		Model* rawModel = mesh->model;

		glBindVertexArray(rawModel->getVaoID());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		meshRenderer->texture->bind();
		if (meshRenderer->texture->hasTransparency) {
			disableCulling();
		}

		program.start();
		program.loadTransformationMatrix(go->transform->getTransformationMatrix());
		program.loadViewMatrix(Camera::mainCamera->getViewMatrix());
		program.loadProjectionMatrix(Camera::mainCamera->projectionMatrix);


		program.loadLight(light);
		program.loadShineVariables(meshRenderer->texture->shineDamper, meshRenderer->texture->reflectivity);
		program.loadSkyColor(Camera::mainCamera->backgroundColor);
		program.loadFogVariables(Camera::mainCamera->fogDensity, Camera::mainCamera->fogGradient);
//		std::cout << Camera::mainCamera->fogGradient << std::endl;


		glDrawElements(GL_TRIANGLES, rawModel->getVertexCount(), GL_UNSIGNED_INT, nullptr);
		program.stop();

		meshRenderer->texture->unbind();
		enableCulling();

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);
	}

	if (terrain != nullptr) {
		Model* rawModel = terrain->model;
		Texture* texture = terrain->texture;

		glBindVertexArray(rawModel->getVaoID());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		texture->bind();

		program.start();
		program.loadTransformationMatrix(go->transform->getTransformationMatrix());
		program.loadViewMatrix(Camera::mainCamera->getViewMatrix());
		program.loadProjectionMatrix(Camera::mainCamera->projectionMatrix);


		program.loadLight(light);
		program.loadShineVariables(texture->shineDamper, texture->reflectivity);
		program.loadSkyColor(Camera::mainCamera->backgroundColor);
		program.loadFogVariables(Camera::mainCamera->fogDensity, Camera::mainCamera->fogGradient);

		glDrawElements(GL_TRIANGLES, rawModel->getVertexCount(), GL_UNSIGNED_INT, nullptr);
		program.stop();

		texture->unbind();

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);
	}
}

void Renderer::enableCulling() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Renderer::disableCulling() {
	glDisable(GL_CULL_FACE);
}