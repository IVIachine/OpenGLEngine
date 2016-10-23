#ifndef _MSG_UPDATE_FLOCKING_
#define _MSG_UPDATE_FLOCKING_

#include "GameMessage.h"

class Message_UpdateFlocking : public GameMessage
{
public:
	Message_UpdateFlocking(
		float aRadius,
		float cRadius,
		float sRadius,
		float aWeight,
		float cWeight,
		float sWeight);

	~Message_UpdateFlocking();

	void process();

private:
	float m_aRadius;
	float m_cRadius;
	float m_sRadius;
	float m_aWeight;
	float m_cWeight;
	float m_sWeight;
};

#endif