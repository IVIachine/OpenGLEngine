#include "Steering.h"
#include "UnitManager.h"

void Steering::update()
{
	Steering* pTemp = getSteering();
	if (pTemp != NULL)
	{
		m_data = pTemp->getData();
	}
}