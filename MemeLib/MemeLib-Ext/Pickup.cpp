#include "Pickup.h"
#include "ResourceManager.h"
#include <GameTime.h>

Pickup::Pickup(Vec3 desiredLoc, PickupType type)
{
	mLoc = desiredLoc;
	mOriginalY = mLoc.y;
	mType = type;
	if (type == PickupType::SPEED_TYPE)
	{
		mSprite = *RESOURCES->getSprite("lightningSprite");
	}
	else if (type == PickupType::HEALTH_TYPE)
	{
		mSprite = *RESOURCES->getSprite("healthSprite");
	}
	else if (type == PickupType::DAMAGE_TYPE)
	{
		mSprite = *RESOURCES->getSprite("damageSprite");
	}
}


Pickup::~Pickup()
{
}

void Pickup::update()
{
	mLoc.y = mOriginalY + (sin(TIME->deltaTime()) * .005); //Needs to be fixed to make bobbing powerup
}

void Pickup::draw()
{
	mSprite.setPosition(mLoc);
	mSprite.draw(*GRAPHICS->getCamera());
}
