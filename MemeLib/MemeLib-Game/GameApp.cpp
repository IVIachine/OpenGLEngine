#include "GameApp.h"
#include "Input.h"
#include "GameController.h"
#include "UnitManager.h"
#include "ComponentManager.h"
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


bool GameApp::loadResources()
{
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

	m_counter = 0.0f;

	Transform tmp = Transform(glm::vec3(1.0, 1.0, 1.0), glm::vec3(45, 0, 0));

	mNavMesh = new NavigationMesh();

	Vertex vertices[] = {
		//Vertices according to faces
		Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.25f, 0.3333f)), //Vertex 0
		Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.5f, 0.3333f)),  //v1
		Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.25f, 0.6666f)),  //v2
		Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.6666f)),   //v3

		Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.5f, 0.3333f)),  //...
		Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.75f, 0.3333f)), //FIx bot coords here
		Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.6666f)),
		Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.75f, 0.6666f)),

		Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.75f, 0.3333f)),
		Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.3333f)),
		Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.75f, 0.6666f)),
		Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 0.6666f)),

		Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.3333f)),
		Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.25f, 0.3333f)),
		Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.6666f)),
		Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.25f, 0.6666f)),

		Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.25f, 0.0f)),
		Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.5f, 0.0f)),
		Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.25f, 0.3333f)),
		Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.5f, 0.3333f)),

		Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.25f, 0.6666f)),
		Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.6666f)),
		Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.25f, 1.0f)),
		Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.5f, 1.0f))
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
	Transform skyBoxTransform = Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(500, 500, 500));
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
	GRAPHICS->moveCamera(GRAPHICS->getCamera());

	if (INPUT->getKey(Keyboard::Up))
	{
		m_position += Vector2::UP;
	}
	if (INPUT->getKey(Keyboard::Down))
	{
		m_position += Vector2::DOWN;
	}
	if (INPUT->getKey(Keyboard::Left))
	{
		m_position += Vector2::LEFT;
	}
	if (INPUT->getKey(Keyboard::Right))
	{
		m_position += Vector2::RIGHT;
	}

	if (INPUT->getKeyDown(Keyboard::Enter))
	{
		GRAPHICS->enableMouseLook(!GRAPHICS->isMouseLookEnabled());
	}

	//GameController::processInput();

	m_skybox->transform().setPos(GRAPHICS->getCamera()->getPos());

	m_counter += 0.0001f;

	GAME->step();

	UNITS->updateAll(TARGET_ELAPSED_MS);
}

void GameApp::draw()
{
	GRAPHICS->clear();
	{
		Camera* cam = GRAPHICS->getCamera();

		m_skybox->draw(*cam);

		mp_volume->draw(*cam);

		std::vector<glm::vec3> temp = mNavMesh->getVerts();

		for (size_t i = 0; i < mNavMesh->getNodeCount(); i++)
		{
			GIZMOS->drawPoint(mNavMesh->getNode(i)->getPosition(), *cam, Transform(mNavMesh->getNode(i)->getPosition(), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)));
		}

		if (m_path.size() > 1)
		{
			for (size_t i = 0; i < m_path.size() - 1; i++)
			{
				Node* prev = m_path[i];
				Node* next = m_path[i + 1];

				_vec3 p1 = prev->getPosition();
				_vec3 p2 = next->getPosition();
				p1.y += .05;
				p2.y += .05;
				GIZMOS->drawRay(p1, p2, *cam, Transform(glm::vec3((p1.x - p2.x)/cam->getFOV(), (p1.y - p2.y)/cam->getFOV(), (p1.z - p2.z)/cam->getFOV()), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
			}
		}

		for (size_t i = 0; i < mNavMesh->edgeCount(); i++)
		{
			_vec3 p1 = mNavMesh->getEdge(i)->first;
			_vec3 p2 = mNavMesh->getEdge(i)->second;
			p1.y += .05;
			p2.y += .05;
			//GIZMOS->drawRay(p1, p2);
		}

		//mp_sprite1->setPosition({ -2.5f, 0.0f , 0.0f});
		//mp_sprite1->setRotation(_vec3(0.0f, 45.f, 0.0f) * Maths::DEG_TO_RAD);
		//mp_sprite1->setScale(_vec3(2.5f, 2.5f, 0.0f));
		//mp_sprite1->draw(*cam);
		
		mp_sprite2->setPosition(mNavMesh->getNode(0)->getPosition());
		mp_sprite2->setRotation(_vec3(180.0f, 0.0f, 0.0f) * Maths::DEG_TO_RAD);
		mp_sprite2->setScale(_vec3(1.0f, 1.0f, 0.0f));
		mp_sprite2->draw(*cam);

		bool toggle = INPUT->getKey(Keyboard::Space);

		float amt = 0.05f;
		_vec3 off = { 0.f, amt, 0.f };
		_vec3 pos = { 0.f, 0.f, 0.f };

		UNITS->drawAll();
	}
	GRAPHICS->flip();
}
