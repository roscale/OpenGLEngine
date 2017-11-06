//
// Created by roscale on 10/25/17.
//

#pragma once


#include "ShaderProgram.hpp"
#include "StaticShader.hpp"
#include "../components/Camera.hpp"
#include "../prefabs/GameObject.hpp"

class Renderer {
public:
	Renderer();

	static void prepare();
	static void render(GameObject* go, StaticShader& program, const GameObject* light);

	static void enableCulling();
	static void disableCulling();
};

