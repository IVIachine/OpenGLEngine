#include "Archer.h"



Archer::Archer()
{
}


Archer::~Archer()
{
}

void Archer::write(RakNet::BitStream & stream) const
{
	stream.Write(mCurrentAction);
	stream.Write(m_pos.x);
	stream.Write(m_pos.y);
	stream.Write(m_pos.z);
	stream.Write(mHealth);
	stream.Write(LINKING->getNetworkId(mTownCenter, false));
}

void Archer::read(RakNet::BitStream & stream, ObjectCreationRegistry* registry)
{
	stream.Read(mCurrentAction);
	stream.Read(m_pos.x);
	stream.Read(m_pos.y);
	stream.Read(m_pos.z);
	stream.Read(mHealth);
	uint32_t centerID;
	stream.Read(centerID);
	mTownCenter = static_cast<TownCenter*>(LINKING->getGameObject(centerID, false, 0, registry));
}

void Archer::writeToFile(std::ofstream& of)
{
	of << "------------------------------------------------------------" << std::endl;
	of << "Archer" << std::endl;
	of << "Archer Action: " << enumToString(mCurrentAction) << std::endl;
	of << "Archer Loc: ( " << std::to_string(m_pos.x) << ", " << std::to_string(m_pos.y) << ", " << std::to_string(m_pos.z) << " )" << std::endl;
	of << "Archer Health: " << std::to_string(mHealth) << std::endl;
	of << "Lives in Center: " << std::endl;
	mTownCenter->writeToFile(of);
}

std::string Archer::enumToString(CurrentAction action)
{
	switch (action)
	{
	case SHOOTING:
	{
		return "Shooting";
	}
	break;
	case IDLE:
	{
		return "Idle";
	}
	break;
	case WALKING:
	{
		return "Walking";
	}
	break;
	default:
	{
		return "Invalid";
	}
		break;
	}
}

void Archer::sendToServer(RakNet::RakPeerInterface * peer)
{
	RakNet::BitStream stream;
	stream.Write((RakNet::MessageID)REPLICATION_PACKET);
	stream.Write(LINKING->getNetworkId(this, true));
	stream.Write(mClassId);
	write(stream);
	peer->Send(&stream, HIGH_PRIORITY, UNRELIABLE, 0, peer->GetSystemAddressFromIndex(0), false);
}

void Archer::sendToServer(RakNet::BitStream & stream)
{
	stream.Write(LINKING->getNetworkId(this, true));
	stream.Write(mClassId);
	write(stream);
}