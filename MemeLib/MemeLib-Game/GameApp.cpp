#include "GameApp.h"
#include "Input.h"
//#include "UnitManager.h"
//#include "ComponentManager.h"
#include "Gizmos.h"
#include "AStarPathfinder.h"

GameApp::GameApp()
{
}

GameApp::~GameApp()
{
	cleanup();
}


bool GameApp::setup(size_t width, size_t height)
{
	return true;
}

void GameApp::cleanup()
{
	unloadResources();
}


void GameApp::moveCamera(Camera* camera)
{
	float cameraSpeed = 0.1f;
	if (INPUT->getKey(Keyboard::W))
	{
		camera->setPos(camera->getPos() + cameraSpeed * camera->getFowardVector());
	}
	if (INPUT->getKey(Keyboard::S))
	{
		camera->setPos(camera->getPos() - cameraSpeed * camera->getFowardVector());
	}
	if (INPUT->getKey(Keyboard::A))
	{
		camera->setPos(camera->getPos() - glm::normalize(glm::cross(camera->getFowardVector(), camera->getUpVector())) * cameraSpeed);
	}
	if (INPUT->getKey(Keyboard::D))
	{
		camera->setPos(camera->getPos() + glm::normalize(glm::cross(camera->getFowardVector(), camera->getUpVector())) * cameraSpeed);
	}
	if (INPUT->getKey(Keyboard::Q))
	{
		camera->setPos(camera->getPos() + Vec3(0.f, 1.f, 0.f));
	}
	if (INPUT->getKey(Keyboard::Z))
	{
		camera->setPos(camera->getPos() - Vec3(0.f, 1.f, 0.f));
	}
}

bool GameApp::loadResources()
{
	/*
	
	if (!ComponentManager::createInstance(MAX_UNITS)->setup())
	{
	fprintf(stderr, "Failed to initialize ComponentManager.\n");
	return false;
	}

	if (!UnitManager::createInstance(MAX_UNITS)->setup())
	{
	fprintf(stderr, "Failed to initialize UnitManager.\n");
	return false;
	}
	
	*/

	m_counter = 0.0f;

	Transform tmp = Transform(Vec3(1.0, 1.0, 1.0), Vec3(45, 0, 0));

	mNavMesh = new NavigationMesh();

	Vertex vertices[] = {
		//Vertices according to faces
		Vertex(Vec3(-1.0f, -1.0f, 1.0f), Vec2(0.25f, 0.3333f)), //Vertex 0
		Vertex(Vec3(1.0f, -1.0f, 1.0f), Vec2(0.5f, 0.3333f)),  //v1
		Vertex(Vec3(-1.0f, 1.0f, 1.0f), Vec2(0.25f, 0.6666f)),  //v2
		Vertex(Vec3(1.0f, 1.0f, 1.0f), Vec2(0.5f, 0.6666f)),   //v3

		Vertex(Vec3(1.0f, -1.0f, 1.0f), Vec2(0.5f, 0.3333f)),  //...
		Vertex(Vec3(1.0f, -1.0f, -1.0f), Vec2(0.75f, 0.3333f)), //FIx bot coords here
		Vertex(Vec3(1.0f, 1.0f, 1.0f), Vec2(0.5f, 0.6666f)),
		Vertex(Vec3(1.0f, 1.0f, -1.0f), Vec2(0.75f, 0.6666f)),

		Vertex(Vec3(1.0f, -1.0f, -1.0f), Vec2(0.75f, 0.3333f)),
		Vertex(Vec3(-1.0f, -1.0f, -1.0f), Vec2(1.0f, 0.3333f)),
		Vertex(Vec3(1.0f, 1.0f, -1.0f), Vec2(0.75f, 0.6666f)),
		Vertex(Vec3(-1.0f, 1.0f, -1.0f), Vec2(1.0f, 0.6666f)),

		Vertex(Vec3(-1.0f, -1.0f, -1.0f), Vec2(0.0f, 0.3333f)),
		Vertex(Vec3(-1.0f, -1.0f, 1.0f), Vec2(0.25f, 0.3333f)),
		Vertex(Vec3(-1.0f, 1.0f, -1.0f), Vec2(0.0f, 0.6666f)),
		Vertex(Vec3(-1.0f, 1.0f, 1.0f), Vec2(0.25f, 0.6666f)),

		Vertex(Vec3(-1.0f, -1.0f, -1.0f), Vec2(0.25f, 0.0f)),
		Vertex(Vec3(1.0f, -1.0f, -1.0f), Vec2(0.5f, 0.0f)),
		Vertex(Vec3(-1.0f, -1.0f, 1.0f), Vec2(0.25f, 0.3333f)),
		Vertex(Vec3(1.0f, -1.0f, 1.0f), Vec2(0.5f, 0.3333f)),

		Vertex(Vec3(-1.0f, 1.0f, 1.0f), Vec2(0.25f, 0.6666f)),
		Vertex(Vec3(1.0f, 1.0f, 1.0f), Vec2(0.5f, 0.6666f)),
		Vertex(Vec3(-1.0f, 1.0f, -1.0f), Vec2(0.25f, 1.0f)),
		Vertex(Vec3(1.0f, 1.0f, -1.0f), Vec2(0.5f, 1.0f))
	};

	size_t indices[]{
		//Faces definition
		0,1,3, 0,3,2,           //Face front
		4,5,7, 4,7,6,           //Face right
		8,9,11, 8,11,10,        //... 
		12,13,15, 12,15,14,
		16,17,19, 16,19,18,
		20,21,23, 20,23,22,
	};

	Shader* p_shader = RESOURCES->addShader("basic", "../Assets/shaders/basicShader");
	Shader* p_shader2 = RESOURCES->addShader("advanced", "../Assets/shaders/basicShader2");

	RESOURCES->addTexture("box", "../Assets/textures/box.png");
	RESOURCES->addTexture("brick", "../Assets/textures/Brick-Texture-1.jpg");
	RESOURCES->addTexture("harambe", "../Assets/textures/Harambe.jpg");
	RESOURCES->addTexture("player", "../Assets/textures/player.png");
	RESOURCES->addTexture("enemy", "../Assets/textures/enemy.png");
	RESOURCES->addTexture("kappa", "../Assets/textures/kappa.png");
	
	RESOURCES->addTexture2D("harambe", RESOURCES->getTexture("harambe"), p_shader);
	RESOURCES->addTexture2D("brick", RESOURCES->getTexture("brick"), p_shader);
	RESOURCES->addTexture2D("player", RESOURCES->getTexture("player"), p_shader);
	RESOURCES->addTexture2D("enemy", RESOURCES->getTexture("enemy"), p_shader);
	RESOURCES->addTexture2D("kappa", RESOURCES->getTexture("kappa"), p_shader);
	
	mp_sprite1 = RESOURCES->addSprite("sprite1", RESOURCES->getTexture2D("harambe"));
	mp_sprite2 = RESOURCES->addSprite("sprite2", RESOURCES->getTexture2D("enemy"));

	mp_volume = new Volume(p_shader2, RESOURCES->getTexture("brick"), "../Assets/obj/test4.obj", false);
	mNavMesh->constructMesh(mp_volume->getMesh());
	mpPathfinder = new AStarPathfinder(mNavMesh);
	Transform skyBoxTransform = Transform(Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(500, 500, 500));
	m_skybox = new Volume(
		p_shader,
		vertices, 
		RESOURCES->getTexture("box"),
		sizeof(vertices) / sizeof(vertices[0]), 
		indices, 
		sizeof(indices) / sizeof(indices[0]), 
		true);

	m_skybox->setTransform(skyBoxTransform);

	m_path = mpPathfinder->findPath(mNavMesh->getNode(5), mNavMesh->getNode(0));

	std::cout
		<< "E: " << mNavMesh->edgeCount() << "\n"
		<< "V: " << mNavMesh->vertCount() << "\n"
		<< "P: " << m_path.size() << "\n";

	return true;
}

void GameApp::unloadResources()
{
	//UnitManager::disposeInstance();
	//ComponentManager::disposeInstance();

	delete m_skybox;
	m_skybox = NULL;

	delete mp_volume;
	mp_volume = NULL;

	delete mNavMesh;
	mNavMesh = NULL;
}


const float TARGET_ELAPSED_MS = LOOP_TARGET_TIME / 1000.0f;

void GameApp::update()
{
	GAME->beginStep();
	moveCamera(GRAPHICS->getCamera());

	if (INPUT->getKey(Keyboard::Up))
	{
		m_position += Vec3_Up;
	}
	if (INPUT->getKey(Keyboard::Down))
	{
		m_position += Vec3_Down;
	}
	if (INPUT->getKey(Keyboard::Left))
	{
		m_position += Vec3_Left;
	}
	if (INPUT->getKey(Keyboard::Right))
	{
		m_position += Vec3_Right;
	}

	if (INPUT->getKeyDown(Keyboard::Enter))
	{
		GRAPHICS->enableMouseLook(!GRAPHICS->isMouseLookEnabled());
	}

	//GameController::processInput();

	m_skybox->transform().setPos(GRAPHICS->getCamera()->getPos());

	m_counter += 0.0001f;

	GAME->step();

	//UNITS->updateAll(TARGET_ELAPSED_MS);
}

void GameApp::draw()
{
	GRAPHICS->clear();
	{
		Camera* cam = GRAPHICS->getCamera();

		m_skybox->draw(*cam);

		mp_volume->draw(*cam);

		std::vector<Vec3> temp = mNavMesh->getVerts();

		for (size_t i = 0; i < mNavMesh->getNodeCount(); i++)
		{
			GIZMOS->drawPoint(mNavMesh->getNode(i)->getPosition());
		}

		if (m_path.size() > 1)
		{
			for (size_t i = 0; i < m_path.size() - 1; i++)
			{
				Node* prev = m_path[i];
				Node* next = m_path[i + 1];

				Vec3 p1 = prev->getPosition();
				Vec3 p2 = next->getPosition();
				p1.y += .05;
				p2.y += .05;
				//GIZMOS->drawRay(p1, p2);
			}
		}

		for (size_t i = 0; i < mNavMesh->edgeCount(); i++)
		{
			Vec3 p1 = mNavMesh->getEdge(i)->first;
			Vec3 p2 = mNavMesh->getEdge(i)->second;
			p1.y += .05;
			p2.y += .05;
			GIZMOS->drawRay(p1, p2);
		}

		//mp_sprite1->setPosition({ -2.5f, 0.0f , 0.0f});
		//mp_sprite1->setRotation(Vec3(0.0f, 45.f, 0.0f) * Maths::DEG_TO_RAD);
		//mp_sprite1->setScale(Vec3(2.5f, 2.5f, 0.0f));
		//mp_sprite1->draw(*cam);
		
		mp_sprite2->setPosition(mNavMesh->getNode(0)->getPosition());
		mp_sprite2->setRotation(Vec3(180.0f, 0.0f, 0.0f) * Maths::DEG_TO_RAD);
		mp_sprite2->setScale(Vec3(1.0f, 1.0f, 0.0f));
		mp_sprite2->draw(*cam);

		bool toggle = INPUT->getKey(Keyboard::Space);

		float amt = 0.05f;
		Vec3 off = { 0.f, amt, 0.f };
		Vec3 pos = { 0.f, 0.f, 0.f };

		//UNITS->drawAll();
	}
	GRAPHICS->flip();
}
