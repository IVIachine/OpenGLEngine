#include "GameController.h"
#include "Game.h"
#include "Input.h"
#include "EventSystem.h"
#include "SpawnEvent.h"
#include "ChangeTargetEvent.h"
#include "BeginPathingEvent.h"
#include "NavMesh.h"
#include "Gizmos.h"
#include "Connection.h"
#include "Common.h"
#include "MousePicker.h"

GameController::GameController()
{
}
void GameController::update(NavMesh* pNavMesh)
{
	if (INPUT->getKeyDown(Keyboard::Up))
	{
		if (m_index + 1 > int(pNavMesh->size()))
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
			m_index = int(pNavMesh->size()) - 1;
		}
		else
		{
			m_index--;
		}
	}

	if (INPUT->getKeyDown(Keyboard::KeyCode::Escape))
	{
		GAME->stop();
	}

	mp_target = pNavMesh->getNode(m_index);

	if (INPUT->getKeyDown(Keyboard::F))
	{
		EVENT_SYSTEM->fireEvent(BeginPathingEvent());
	}
	if (INPUT->getKeyDown(Keyboard::Enter))
	{
		GRAPHICS->enableMouseLook(!GRAPHICS->isMouseLookEnabled());
	}
	if (INPUT->getKeyDown(Keyboard::P))
	{
		EVENT_SYSTEM->fireEvent(SpawnEvent());
	}

	if (INPUT->getKeyDown(Keyboard::G))
	{
		if (mDebugMode)
			mDebugMode = false;
		else
			mDebugMode = true;
	}

	moveCamera(GRAPHICS->getCamera());
}

void GameController::draw(NavMesh* pNavMesh, MousePicker* picker)
{
	// draw verts, edges, and target node
	if (mDebugMode)
	{
		/*for (size_t i = 0; i < pNavMesh->size(); i++)
		{
			GIZMOS->drawPoint(pNavMesh->getNode(i)->getPosition());
		}
		
		for (size_t i = 0; i < pNavMesh->edgeCount(); i++)
		{

				Vec3 p1 = pNavMesh->getEdge(i)->first;
				Vec3 p2 = pNavMesh->getEdge(i)->second;
				p1.y += 0.05f;
				p2.y += 0.05f;
				GIZMOS->drawRay(p1, p2);
		}
		*/

		Vec3 p1 = GRAPHICS->getCamera()->getPosition();
		Vec3 p2 = GRAPHICS->getCamera()->getPosition() + picker->getRay();
		p2 *= 100;
		//p1.y -= 0.01f; //May need these two lines
		//p2.y -= 0.01f;
		//std::cout << "Cam: " << p1.x << " " << p1.y << " " << p1.z << std::endl;
		//std::cout <<  "Targ: " << p2.x << " " << p2.y << " " << p2.z << std::endl;
		GIZMOS->drawRay(p1, p2);

		//for (size_t i = 0; i < pNavMesh->faceCount(); i++)
		/*{
			for (size_t j = 0; j < pNavMesh->getFaces()[currentIndex].edges.size(); j++)
			{
				Vec3 p1 = pNavMesh->getFaces()[currentIndex].edges[j].first;
				Vec3 p2 = pNavMesh->getFaces()[currentIndex].edges[j].second;
				p1.y += 0.05f;
				p2.y += 0.05f;
				GIZMOS->drawRay(p1, p2);
			}
		}*/

	}

	mp_target = pNavMesh->getNode(m_index);

	if (mp_target)
	{
		GIZMOS->drawPoint(mp_target->getPosition() + Vec3(0.f, 0.5f, 0.f));
		EVENT_SYSTEM->fireEvent(ChangeTargetEvent(mp_target->getPosition()));
	}


	if (!CLIENT->isConnected())
	{
		if (INPUT->getKeyDown(Keyboard::C))
		{
			std::cout << "Connecting to server... \n";
			CLIENT->connect("127.0.0.1");
		}
	}
	else
	{
		if (INPUT->getKeyDown(Keyboard::M))
		{
			sendMessage("Hello, World!");
		}
	}
}

void GameController::moveCamera(Camera* camera)
{
	float cameraSpeed = 0.1f;
	if (INPUT->getKey(Keyboard::W))
	{
		camera->setPosition(camera->getPosition() + cameraSpeed * camera->getFoward());
	}
	if (INPUT->getKey(Keyboard::S))
	{
		camera->setPosition(camera->getPosition() - cameraSpeed * camera->getFoward());
	}
	if (INPUT->getKey(Keyboard::A))
	{
		camera->setPosition(camera->getPosition() - glm::normalize(glm::cross(camera->getFoward(), camera->getUp())) * cameraSpeed);
	}
	if (INPUT->getKey(Keyboard::D))
	{
		camera->setPosition(camera->getPosition() + glm::normalize(glm::cross(camera->getFoward(), camera->getUp())) * cameraSpeed);
	}
	if (INPUT->getKey(Keyboard::Q))
	{
		camera->setPosition(camera->getPosition() + Vec3(0.f, 1.f, 0.f));
	}
	if (INPUT->getKey(Keyboard::Z))
	{
		camera->setPosition(camera->getPosition() - Vec3(0.f, 1.f, 0.f));
	}
}