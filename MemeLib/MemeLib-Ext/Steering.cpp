#include "Steering.h"


void Steering::update()
{
	Steering* pTemp = getSteering();
	if (pTemp != NULL)
	{
		this->mData = pTemp->getData();
	}
}
