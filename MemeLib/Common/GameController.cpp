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

void GameController::update(NavMesh* pNavMesh, MousePicker* picker)
{
	RayCastHit hit;
	if (picker->raycast(GRAPHICS->getCamera()->getPosition(), GRAPHICS->getCamera()->getFoward(), hit))
	{
		Vec3 point = hit.point;
		mp_target = pNavMesh->getNode(point);
	}

	if (INPUT->getButtonDown(Mouse::Buttons::Left))
	{
		EVENT_SYSTEM->fireEvent(BeginPathingEvent());
	}

	if (INPUT->getKeyDown(Keyboard::KeyCode::Escape))
	{
		GAME->stop();
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

	if (INPUT->getKeyDown(Keyboard::Enter))
	{
		GRAPHICS->enableMouseLook(!GRAPHICS->isMouseLookEnabled());
		GRAPHICS->toggleMouse();
	}
	if (!GRAPHICS->isMouseLookEnabled())
	{
		GRAPHICS->getCamera()->setForward({ GRAPHICS->getCamera()->getFoward() });
	}

	picker->update();
}

void GameController::draw(NavMesh* pNavMesh, MousePicker* picker)
{
	if (mp_target)
	{
		GIZMOS->drawPoint(mp_target->getPosition() + Vec3(0.f, 0.5f, 0.f));
		EVENT_SYSTEM->fireEvent(ChangeTargetEvent(mp_target->getPosition()));
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