#include "GameController.h"
#include "ResourceManager.h"
#include "Input.h"
#include "UnitManager.h"
#include "Graphics.h"
#include "Maths.h"
#include "GameMessageManager.h"

#include "Message_PlayerMoveTo.h"
#include "Message_ExitApplication.h"
#include "Message_CreateUnit.h"
#include "Message_DeleteUnit.h"
#include "Message_UpdateFlocking.h"


void GameController::processInput()
{
	// Left Mouse Button click directs player Unit to clicked location (use ArriveAndFaceSteering)
	if (INPUT->getButton(Mouse::Left))
	{
		//MESSAGES->addMessage(new Message_PlayerMoveTo(INPUT->mousePosition()));
	}

	// ‘Esc’ exits the game
	if (INPUT->getKeyDown(Keyboard::Escape))
	{
		MESSAGES->addMessage(new Message_ExitApplication());
	}

	// When user hits the Enter key, add a unit at a random location on
	// the screen and have it run the WanderAndChase steering behavior
	if (INPUT->getKeyDown(Keyboard::A))
	{
		for (int i = 0; i < 1; i++)
		{
			MESSAGES->addMessage(new Message_CreateUnit());
		}
	}

	// When the user hits the ‘D’ key delete a random unit (not the player, though)
	if (INPUT->getKeyDown(Keyboard::D))
	{
		MESSAGES->addMessage(new Message_DeleteUnit());
	}
}