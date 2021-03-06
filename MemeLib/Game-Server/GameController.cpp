#include "GameController.h"
#include "Game.h"
#include "Input.h"
#include "EventSystem.h"
#include "SpawnEvent.h"
#include "ChangeTargetEvent.h"
#include "BeginPathingEvent.h"
#include "NavMesh.h"
#include "Gizmos.h"

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

void GameController::draw(NavMesh* pNavMesh)
{
	// draw verts, edges, and target node

	if (mDebugMode)
	{
		for (size_t i = 0; i < pNavMesh->size(); i++)
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
	}

	mp_target = pNavMesh->getNode(m_index);

	if (mp_target)
	{
		GIZMOS->drawPoint(mp_target->getPosition() + Vec3(0.f, 0.5f, 0.f));
		EVENT_SYSTEM->fireEvent(ChangeTargetEvent(mp_target->getPosition()));
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