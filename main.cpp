#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "rendering/DisplayManager.hpp"
#include "rendering/Loader.hpp"
#include "rendering/Renderer.hpp"
#include "core/World.hpp"
#include "components/MeshRenderer.hpp"
#include "rendering/OBJLoader.hpp"
#include "components/Light.hpp"
#include "components/Terrain.hpp"
#include "core/InputManager.hpp"
#include "core/Script.hpp"
#include "settings.hpp"
#include "core/Time.hpp"


std::vector<float> quadVertices = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
};

std::vector<unsigned int> quadIndices = {
		0, 1, 3,
		3, 1, 2
};

std::vector<float> quadTextureCoords = {
		0, 0,
		0, 1,
		1, 1,
		1, 0
};


class FollowPlayerScript : public Script {
private:
	Transform* playerTransform;

	float distance = 10.0f;

	glm::vec3 offsetPosition = glm::vec3(0, 3, 0);
	glm::vec3 offsetRotation = glm::vec3(0, 0, 0);

public:
	void onStart() override {
		playerTransform = World::find("Player")->transform;
	}

	void onUpdate() override {
		gameObject->transform->rotation.x = playerTransform->rotation.x + offsetRotation.x;
		gameObject->transform->rotation.y = playerTransform->rotation.y + glm::pi<float>() + offsetRotation.y;
		gameObject->transform->rotation.z = playerTransform->rotation.z + offsetRotation.z;

		gameObject->transform->position.y = playerTransform->position.y - (std::sin(gameObject->transform->rotation.x) * distance);
		gameObject->transform->position.x = playerTransform->position.x + (std::sin(gameObject->transform->rotation.y) * distance) * std::cos(gameObject->transform->rotation.x);
		gameObject->transform->position.z = playerTransform->position.z + (std::cos(gameObject->transform->rotation.y) * distance) * std::cos(gameObject->transform->rotation.x);

		gameObject->transform->position.x += offsetPosition.x;
		gameObject->transform->position.y += offsetPosition.y;
		gameObject->transform->position.z += offsetPosition.z;
	}

	void onMouseMotion(double xabs, double yabs, double xrel, double yrel) override {
		offsetRotation.x -= yrel * Time::deltaTime * settings::MOUSE_SENSIBILITY / 30.0f;
		offsetRotation.x = glm::clamp(offsetRotation.x, (float)glm::radians(-90.0f), (float)glm::radians(90.0f));
	}

	void onMouseScroll(double xoffset, double yoffset) override {
		distance -= yoffset;
		distance = std::max(3.0f, distance);
		distance = std::min(20.0f, distance);
	}

	std::string classStr() const override {
		return "FollowPlayerScript";
	}

	Component* clone() const override {
		return new FollowPlayerScript(*this);
	}
};

class WASDMove : public Script {
private:
	float force = 10.0f;

public:
	void onUpdate() override {
		if (glfwGetKey(DisplayManager::window, GLFW_KEY_W) == GLFW_PRESS) {
			float dx = std::sin(gameObject->transform->rotation.y) * force;
			float dz = std::cos(gameObject->transform->rotation.y) * force;

			gameObject->transform->translate(glm::vec3(dx, 0, dz) * Time::deltaTime);
		}
		if (glfwGetKey(DisplayManager::window, GLFW_KEY_S) == GLFW_PRESS) {
			float dx = std::sin(gameObject->transform->rotation.y) * force;
			float dz = std::cos(gameObject->transform->rotation.y) * force;

			gameObject->transform->translate(glm::vec3(-dx, 0, -dz) * Time::deltaTime);
		}

		if (glfwGetKey(DisplayManager::window, GLFW_KEY_A) == GLFW_PRESS) {
			float dx = std::sin(gameObject->transform->rotation.y + glm::half_pi<float>()) * force;
			float dz = std::cos(gameObject->transform->rotation.y + glm::half_pi<float>()) * force;

			gameObject->transform->translate(glm::vec3(dx, 0, dz) * Time::deltaTime);
		}
		if (glfwGetKey(DisplayManager::window, GLFW_KEY_D) == GLFW_PRESS) {
			float dx = std::sin(gameObject->transform->rotation.y - glm::half_pi<float>()) * force;
			float dz = std::cos(gameObject->transform->rotation.y - glm::half_pi<float>()) * force;

			gameObject->transform->translate(glm::vec3(dx, 0, dz) * Time::deltaTime);
		}
	}

	void onMouseMotion(double xabs, double yabs, double xrel, double yrel) override {
		gameObject->transform->rotation.y -= xrel * Time::deltaTime * settings::MOUSE_SENSIBILITY / 30.0f;
	}

	std::string classStr() const override {
		return "WASDMove";
	}

	Component* clone() const override {
		return new WASDMove(*this);
	}
};


int main() {
	DisplayManager::createDisplay(800, 600, "My OpenGL thing");
	Renderer renderer;

	auto program = StaticShader::createShaderProgram("shaders/vertShader.glsl", "shaders/fragShader.glsl");


	GameObject* fruits = new GameObject();
	fruits->addComponent(new Mesh());
	fruits->addComponent(new MeshRenderer());

	Model* model = OBJLoader::loadObjModel("res/models/stall.obj");

	Mesh* mesh = reinterpret_cast<Mesh*>(fruits->getComponent("Mesh"));
	mesh->model = model;

	Texture* texture = new Texture(Loader::loadTexture("res/textures/stall.bmp"));
	texture->shineDamper = 10;
	texture->reflectivity = 0.4;

	MeshRenderer* meshRenderer = reinterpret_cast<MeshRenderer*>(fruits->getComponent("MeshRenderer"));
	meshRenderer->texture = texture;



	GameObject* airplane = new GameObject();
	airplane->addComponent(new Mesh());
	airplane->addComponent(new MeshRenderer());

	Model* airplaneModel = OBJLoader::loadObjModel("res/models/airplane.obj");

	Mesh* airplaneMesh = reinterpret_cast<Mesh*>(airplane->getComponent("Mesh"));
	airplaneMesh->model = airplaneModel;

	Texture* airplaneTexture = new Texture(Loader::loadTexture("res/textures/pixel.bmp"));
	airplaneTexture->shineDamper = 10;
	airplaneTexture->reflectivity = 0.4;

	MeshRenderer* airplaneMeshRenderer = reinterpret_cast<MeshRenderer*>(airplane->getComponent("MeshRenderer"));
	airplaneMeshRenderer->texture = airplaneTexture;



	GameObject* fern = new GameObject();
	fern->addComponent(new Mesh());
	fern->addComponent(new MeshRenderer());

	Model* fernModel = OBJLoader::loadObjModel("res/models/fern.obj");

	Mesh* fernMesh = reinterpret_cast<Mesh*>(fern->getComponent("Mesh"));
	fernMesh->model = fernModel;

	Texture* fernTexture = new Texture(Loader::loadTexture("res/textures/fern.bmp"));
	fernTexture->shineDamper = 10;
	fernTexture->reflectivity = 0.2;
	fernTexture->hasTransparency = true;

	MeshRenderer* fernMeshRenderer = reinterpret_cast<MeshRenderer*>(fern->getComponent("MeshRenderer"));
	fernMeshRenderer->texture = fernTexture;



	GameObject* tree = new GameObject();
	tree->addComponent(new Mesh());
	tree->addComponent(new MeshRenderer());

	Model* treeModel = OBJLoader::loadObjModel("res/models/tree.obj");

	Mesh* treeMesh = reinterpret_cast<Mesh*>(tree->getComponent("Mesh"));
	treeMesh->model = treeModel;

	Texture* treeTexture = new Texture(Loader::loadTexture("res/textures/tree.bmp"));
	treeTexture->shineDamper = 10;
	treeTexture->reflectivity = 0.2;
//	treeTexture->hasTransparency = true;

	MeshRenderer* treeMeshRenderer = reinterpret_cast<MeshRenderer*>(tree->getComponent("MeshRenderer"));
	treeMeshRenderer->texture = treeTexture;



	GameObject* quad = new GameObject();
	quad->addComponent(new Mesh());
	quad->addComponent(new MeshRenderer());

	auto normals = std::vector<float>();
	for (int i = 0; i < 4; i++) {
		normals.push_back(0);
		normals.push_back(1);
		normals.push_back(0);
	}

	Model* quadModel = Loader::loadToVAO(quadVertices, quadTextureCoords, normals, quadIndices);

	Mesh* quadMesh = reinterpret_cast<Mesh*>(quad->getComponent("Mesh"));
	quadMesh->model = quadModel;

	Texture* quadTexture = new Texture(Loader::loadTexture("res/textures/wallpaper.bmp"));
//	quadTexture->shineDamper = 10;
//	quadTexture->reflectivity = 0.4;

	MeshRenderer* quadMeshRenderer = reinterpret_cast<MeshRenderer*>(quad->getComponent("MeshRenderer"));
	quadMeshRenderer->texture = quadTexture;

//	quad->addComponent(new AlwaysFacingCamera());



	GameObject* light = new GameObject();
	light->addComponent(new Light());

	Light* lightComponent = reinterpret_cast<Light*>(light->getComponent("Light"));
	lightComponent->color = {1, 1, 1};





	GameObject* terrain = new GameObject();
	terrain->addComponent(new Terrain());
	Terrain* terrainComponent = reinterpret_cast<Terrain*>(terrain->getComponent("Terrain"));
	terrainComponent->length = 80;
	terrainComponent->width = 80;

	Bitmap* highmap = new Bitmap("res/textures/highmap.bmp");
	std::cout << highmap->width << " " << highmap->width << std::endl;
	terrainComponent->highmap = highmap;

	terrainComponent->generateTerrain(8, 8);

	Texture* terrainTexture = new Texture(Loader::loadTexture("res/textures/grass.bmp"));
	terrainTexture->shineDamper = 10;
	terrainTexture->reflectivity = 0;
	terrainComponent->texture = terrainTexture;


	GameObject* player = new GameObject();
	player->name = "Player";

	player->addComponent(new Mesh());
	player->addComponent(new MeshRenderer());

	Model* playerModel = OBJLoader::loadObjModel("res/models/player.obj");

	Mesh* playerMesh = reinterpret_cast<Mesh*>(player->getComponent("Mesh"));
	playerMesh->model = playerModel;

	Texture* playerTexture = new Texture(Loader::loadTexture("res/textures/player.bmp"));
	playerTexture->shineDamper = 10;
	playerTexture->reflectivity = 0.2;
//	playerTexture->hasTransparency = true;

	MeshRenderer* playerMeshRenderer = reinterpret_cast<MeshRenderer*>(player->getComponent("MeshRenderer"));
	playerMeshRenderer->texture = playerTexture;

	player->addComponent(new WASDMove());


	GameObject* camera = new GameObject();
	camera->addComponent(new Camera());
	Camera* cameraComponent1 = reinterpret_cast<Camera*>(camera->getComponent("Camera"));
	cameraComponent1->FOV = 60.0f;
	cameraComponent1->createProjectionMatrix();
	cameraComponent1->backgroundColor = glm::vec4(0, 0.8, 1, 1);

	camera->addComponent(new FollowPlayerScript());

//	camera->addComponent(new WASDMove());






	GameObject* lightInstance = World::instantiate(light, {25.0f, 20.0f, 25.0f});
	GameObject* terrainInstance = World::instantiate(terrain);
	GameObject* fruitsInstance = World::instantiate(fruits, {25, 0, 25});
	GameObject* fernInstance = World::instantiate(fern, {45, 0, 25}, {0, 0, 0}, {0.8f, 0.8f ,0.8f});
	GameObject* airplaneInstance = World::instantiate(airplane, {35, 0, 25});
	GameObject* treeInstance = World::instantiate(tree, {55, 0, 25}, {0, 0, 0}, {5, 5, 5});
	GameObject* quadInstance = World::instantiate(quad, {10, 7, 20}, {0, 0, 0}, {10, 10, 10});
	GameObject* playerInstance = World::instantiate(player, {65, 0, 20}, {0, 0, 0}, {0.4, 0.4, 0.4});
	GameObject* cameraInstance = World::instantiate(camera, {25, 4.0f, 50});
	Camera* cameraComponent = reinterpret_cast<Camera*>(cameraInstance->getComponent("Camera"));
	cameraComponent->setMainCamera();

	fruitsInstance->transform->rotate(0, 3.14, 0);
	airplaneInstance->transform->rotate(0, -0.5f, 0);

	quadInstance->transform->rotate(0, 1, 0);


	glfwSetInputMode(DisplayManager::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	InputManager::init();
	Time::init();

	World::start();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(DisplayManager::window))
	{
		World::update();

		Renderer::prepare();

		for (const auto& gameObject : World::gameObjects) {
			Renderer::render(gameObject, program, lightInstance);
		}

		DisplayManager::updateDisplay();
		Time::update();
	}

	DisplayManager::closeDisplay();
	return 0;
}