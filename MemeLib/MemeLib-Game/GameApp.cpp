#include "GameApp.h"
#include "Input.h"
#include "Gizmos.h"
#include "AStarPathfinder.h"
#include "EventSystem.h"
#include "SpawnEvent.h"

GameApp::GameApp()
{
	EVENT_SYSTEM->addListener(SPAWN_EVENT, this);
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
	if (!ComponentManager::createInstance(100)->setup())
	{
		fprintf(stderr, "Failed to initialize Time.\n");
		return false;
	}

	if (!UnitManager::createInstance(100)->setup())
	{
		fprintf(stderr, "Failed to initialize Time.\n");
		return false;
	}

	m_counter = 0.0f;

	mNavMesh = new NavMesh();

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
	
	Sprite* mp_sprite2 = RESOURCES->addSprite("sprite2", RESOURCES->getTexture2D("harambe"));
	RESOURCES->getSprite("sprite2")->setScale(Vec3(.1f,.1f,.1f));
	RESOURCES->getSprite("sprite2")->setRotation(Vec3(270,0,0) * Maths::DEG_TO_RAD);
	mp_volume = new Volume(p_shader2, RESOURCES->getTexture("brick"), "../Assets/obj/test4.obj", false);
	mNavMesh->constructMesh(mp_volume->getMesh());
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

	return true;
}

void GameApp::unloadResources()
{
	UnitManager::disposeInstance();
	ComponentManager::disposeInstance();
	

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

	if (INPUT->getKeyDown(Keyboard::Up))
	{
		if (m_index + 1 > mNavMesh->size())
		{
			m_index = 0;
		}
		else
		{
			m_index++;
		}
	}
	if (INPUT->getKeyDown(Keyboard::Down))
	{
		if (m_index - 1 < 0)
		{
			m_index = mNavMesh->size() - 1;
		}
		else
		{
			m_index--;
		}
	}

	if (INPUT->getKeyDown(Keyboard::Space))
	{
		
	}

	if (INPUT->getKeyDown(Keyboard::Enter))
	{
		GRAPHICS->enableMouseLook(!GRAPHICS->isMouseLookEnabled());
	}

	if (INPUT->getKeyDown(Keyboard::P))
	{
		EVENT_SYSTEM->fireEvent(SpawnEvent());
	}
	//GameController::processInput();

	m_skybox->transform().setPos(GRAPHICS->getCamera()->getPos());

	m_counter += 0.0001f;

	GAME->step();

	COMPONENTS->update(TARGET_ELAPSED_MS);
	UNITS->updateAll(TARGET_ELAPSED_MS);
}

void GameApp::draw()
{
	GRAPHICS->clear();
	{
		Camera* cam = GRAPHICS->getCamera();

		m_skybox->draw(*cam);

		mp_volume->draw(*cam);

		std::vector<Vec3> temp = mNavMesh->getVerts();

		for (size_t i = 0; i < mNavMesh->size(); i++)
		{
			GIZMOS->drawPoint(mNavMesh->getNode(i)->getPosition());
		}

		for (size_t i = 0; i < mNavMesh->edgeCount(); i++)
		{
			Vec3 p1 = mNavMesh->getEdge(i)->first;
			Vec3 p2 = mNavMesh->getEdge(i)->second;
			p1.y += 0.05f;
			p2.y += 0.05f;
			GIZMOS->drawRay(p1, p2);
		}

		mp_target = mNavMesh->getNode(m_index);
		if (mp_target)
		{
			GIZMOS->drawPoint(mp_target->getPosition() + Vec3(0.f, 0.5f, 0.f));
		}

		UNITS->drawAll();
	}
	GRAPHICS->flip();
}

void GameApp::handleEvent(const Event & ev)
{
	if (ev.getType() == SPAWN_EVENT)
	{
		UNITS->deleteAll();
		for (int i = 0; i < 10; i++)
		{
			int randIndex;
			randIndex = rand() % (mNavMesh->getVerts().size() - 1);
			Unit* pUnit = UNITS->createUnit(*RESOURCES->getSprite("sprite2"), mNavMesh, true, PositionData(mNavMesh->getNode(randIndex)->getPosition(), 0));
			
			pUnit->setSteering(Steering::PATH_FOLLOW);
			pUnit->findPath(mp_target->getPosition());
		}
	}
}