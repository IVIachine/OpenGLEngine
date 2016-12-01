#include "GameApp.h"
#include "Input.h"
#include "Gizmos.h"
#include "AStarPathfinder.h"
#include "EventSystem.h"
#include "SpawnEvent.h"
#include "GameController.h"
#include "GameObjectManager.h"

GameApp::GameApp()
{
	
}

GameApp::~GameApp()
{
	//clear();
}


bool GameApp::setup()
{
	EVENT_SYSTEM->addListener(SPAWN_EVENT, this);

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

	mp_navMesh = new NavMesh();

	Vertex vertices[] = {
		//Vertices according to faces
		Vertex(Vec3(-1.0f, -1.0f, 1.0f),	Vec2(0.25f, 0.3333f)),	//Vertex 0
		Vertex(Vec3(1.0f, -1.0f, 1.0f),		Vec2(0.5f, 0.3333f)),	//v1
		Vertex(Vec3(-1.0f, 1.0f, 1.0f),		Vec2(0.25f, 0.6666f)),  //v2
		Vertex(Vec3(1.0f, 1.0f, 1.0f),		Vec2(0.5f, 0.6666f)),   //v3

		Vertex(Vec3(1.0f, -1.0f, 1.0f),		Vec2(0.5f, 0.3333f)),	//...
		Vertex(Vec3(1.0f, -1.0f, -1.0f),	Vec2(0.75f, 0.3333f)),	//FIx bot coords here
		Vertex(Vec3(1.0f, 1.0f, 1.0f),		Vec2(0.5f, 0.6666f)),
		Vertex(Vec3(1.0f, 1.0f, -1.0f),		Vec2(0.75f, 0.6666f)),

		Vertex(Vec3(1.0f, -1.0f, -1.0f),	Vec2(0.75f, 0.3333f)),
		Vertex(Vec3(-1.0f, -1.0f, -1.0f),	Vec2(1.0f, 0.3333f)),
		Vertex(Vec3(1.0f, 1.0f, -1.0f),		Vec2(0.75f, 0.6666f)),
		Vertex(Vec3(-1.0f, 1.0f, -1.0f),	Vec2(1.0f, 0.6666f)),

		Vertex(Vec3(-1.0f, -1.0f, -1.0f),	Vec2(0.0f, 0.3333f)),
		Vertex(Vec3(-1.0f, -1.0f, 1.0f),	Vec2(0.25f, 0.3333f)),
		Vertex(Vec3(-1.0f, 1.0f, -1.0f),	Vec2(0.0f, 0.6666f)),
		Vertex(Vec3(-1.0f, 1.0f, 1.0f),		Vec2(0.25f, 0.6666f)),

		Vertex(Vec3(-1.0f, -1.0f, -1.0f),	Vec2(0.25f, 0.0f)),
		Vertex(Vec3(1.0f, -1.0f, -1.0f),	Vec2(0.5f, 0.0f)),
		Vertex(Vec3(-1.0f, -1.0f, 1.0f),	Vec2(0.25f, 0.3333f)),
		Vertex(Vec3(1.0f, -1.0f, 1.0f),		Vec2(0.5f, 0.3333f)),

		Vertex(Vec3(-1.0f, 1.0f, 1.0f),		Vec2(0.25f, 0.6666f)),
		Vertex(Vec3(1.0f, 1.0f, 1.0f),		Vec2(0.5f, 0.6666f)),
		Vertex(Vec3(-1.0f, 1.0f, -1.0f),	Vec2(0.25f, 1.0f)),
		Vertex(Vec3(1.0f, 1.0f, -1.0f),		Vec2(0.5f, 1.0f))
	};

	size_t indices[]{
		//Faces definition
		0,1,3,		0,3,2,      //Face front
		4,5,7,		4,7,6,		//Face right
		8,9,11,		8,11,10,    //... 
		12,13,15,	12,15,14,
		16,17,19,	16,19,18,
		20,21,23,	20,23,22,
	};

	Shader* p_shader = RESOURCES->addShader("basic", "../Assets/shaders/basicShader");
	Shader* p_shader2 = RESOURCES->addShader("advanced", "../Assets/shaders/basicShader2");

	RESOURCES->addTexture("box",		"../Assets/textures/box.png");
	RESOURCES->addTexture("lightning",		"../Assets/textures/irboost.png");
	RESOURCES->addTexture("health", "../Assets/textures/health.png");
	RESOURCES->addTexture("damage", "../Assets/textures/plus.png");
	RESOURCES->addTexture("player",		"../Assets/textures/player.png");
	RESOURCES->addTexture("enemyIdle",		"../Assets/textures/enemy1.png");
	RESOURCES->addTexture("enemyChase", "../Assets/textures/enemy2.png");
	RESOURCES->addTexture("enemyPickup", "../Assets/textures/enemy3.png");
	//CITE: https://irboost.com/img/irboost.png
	//CITE: http://pngimg.com/upload/small/binocular_PNG12921.png
	//CITE: http://www.free-icons-download.net/images/first-aid-kit-icon-29793.png
	//CITE: http://cdn.bulbagarden.net/upload/1/1a/Prop_Top_Hat_Sprite.png
	RESOURCES->addTexture2D("lightning",	RESOURCES->getTexture("lightning"),		p_shader);
	RESOURCES->addTexture2D("health", RESOURCES->getTexture("health"), p_shader);
	RESOURCES->addTexture2D("damage", RESOURCES->getTexture("damage"), p_shader);
	RESOURCES->addTexture2D("player",	RESOURCES->getTexture("player"),	p_shader);
	RESOURCES->addTexture2D("enemyIdle",	RESOURCES->getTexture("enemyIdle"),		p_shader);
	RESOURCES->addTexture2D("enemyChase", RESOURCES->getTexture("enemyChase"), p_shader);
	RESOURCES->addTexture2D("enemyPickup", RESOURCES->getTexture("enemyPickup"), p_shader);

	Sprite* pSpr11 = RESOURCES->addSprite("idle", RESOURCES->getTexture2D("enemyIdle"));
	pSpr11->setScale(Vec3(.1f, .1f, .1f));
	pSpr11->setRotation(Vec3(270, 0, 0) * Maths::DEG_TO_RAD);

	Sprite* pSpr12 = RESOURCES->addSprite("chase", RESOURCES->getTexture2D("enemyChase"));
	pSpr12->setScale(Vec3(.1f, .1f, .1f));
	pSpr12->setRotation(Vec3(270, 0, 0) * Maths::DEG_TO_RAD);

	Sprite* pSpr13 = RESOURCES->addSprite("pickup", RESOURCES->getTexture2D("enemyPickup"));
	pSpr13->setScale(Vec3(.1f, .1f, .1f));
	pSpr13->setRotation(Vec3(270, 0, 0) * Maths::DEG_TO_RAD);


	Sprite* pSpr2 = RESOURCES->addSprite("lightningSprite", RESOURCES->getTexture2D("lightning"));
	pSpr2->setScale(Vec3(.1f, .1f, .1f));
	pSpr2->setRotation(Vec3(270, 0, 0) * Maths::DEG_TO_RAD);

	Sprite* pSpr3 = RESOURCES->addSprite("healthSprite", RESOURCES->getTexture2D("health"));
	pSpr3->setScale(Vec3(.1f, .1f, .1f));
	pSpr3->setRotation(Vec3(270, 0, 0) * Maths::DEG_TO_RAD);

	Sprite* pSpr4 = RESOURCES->addSprite("player", RESOURCES->getTexture2D("player"));
	pSpr4->setScale(Vec3(.1f, .1f, .1f));
	pSpr4->setRotation(Vec3(270, 0, 0) * Maths::DEG_TO_RAD);

	Sprite* pSpr5 = RESOURCES->addSprite("damageSprite", RESOURCES->getTexture2D("damage"));
	pSpr5->setScale(Vec3(.1f, .1f, .1f));
	pSpr5->setRotation(Vec3(270, 0, 0) * Maths::DEG_TO_RAD);

	mp_volume = new Volume(p_shader2, RESOURCES->getTexture("lightning"), "../Assets/obj/test4.obj", false);
	mp_navMesh->constructMesh(mp_volume->getMesh());
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

	// https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_01#The_FreeType_library
	RESOURCES->addShader("text", "../Assets/shaders/text");
	RESOURCES->addFont("cour", "../Assets/fonts/cour.ttf");
	
	mp_picker = new MousePicker(mp_navMesh);
	mp_enemySpawner = new EnemySpawner(10000, Vec3(0,0,0));
	mp_pickupSpawner = new PickupSpawner(4000);
	int randIndex;
	randIndex = rand() % (mp_navMesh->getVerts().size());

	Unit* pPlayer = UNITS->createUnit(
		*RESOURCES->getSprite("player"),
		mp_navMesh,
		200,
		3,
		.3,
		true,
		PositionData(mp_navMesh->getNode(randIndex)->getPosition(), 0), 
		ZERO_PHYSICS_DATA);
	
	pPlayer->setSteering(Steering::PATH_FOLLOW);

	Unit::setPlayerID(pPlayer->getID());

	std::cout << "PLAYER ID " << Unit::getPlayerID() << "\n";

	return true;
}

void GameApp::clear()
{
	UNITS->deleteAll();
	UnitManager::disposeInstance();

	ComponentManager::disposeInstance();

	delete m_skybox;
	m_skybox = NULL;

	delete mp_volume;
	mp_volume = NULL;

	delete mp_navMesh;
	mp_navMesh = NULL;

	delete mp_enemySpawner;
	mp_enemySpawner = NULL;

	delete mp_pickupSpawner;
	mp_pickupSpawner = NULL;
}

void GameApp::update()
{
	m_skybox->transform().setPosition(GRAPHICS->getCamera()->getPosition());
	m_controller.update(mp_navMesh, mp_picker);
	mp_enemySpawner->update(mp_navMesh);
	mp_pickupSpawner->update(mp_navMesh);
	COMPONENTS->update(FIXED_UPDATE_DELTA);
}

void GameApp::draw()
{
	Camera* cam = GRAPHICS->getCamera();

	m_skybox->draw(*cam);

	mp_volume->draw(*cam);

	m_controller.draw(mp_navMesh, mp_picker);	
}

void GameApp::handleEvent(const Event & ev)
{
	if (ev.getType() == SPAWN_EVENT)
	{
		
	}
}