#include "TownCenter.h"



TownCenter::TownCenter()
{
}


TownCenter::~TownCenter()
{
}

void TownCenter::write(RakNet::BitStream & stream) const
{
	stream.Write(mType);
	stream.Write(mLoc.x);
	stream.Write(mLoc.y);
	stream.Write(mLoc.z);
	stream.Write(mHealth);
}

void TownCenter::sendToServer(RakNet::RakPeerInterface * peer)
{
	RakNet::BitStream stream;
	stream.Write((RakNet::MessageID)REPLICATION_PACKET);
	stream.Write(LINKING->getNetworkId(this, true));
	stream.Write(mClassId);
	write(stream);
	peer->Send(&stream, HIGH_PRIORITY, UNRELIABLE, 0, peer->GetSystemAddressFromIndex(0), false);
}

void TownCenter::sendToServer(RakNet::BitStream & stream)
{
	stream.Write(LINKING->getNetworkId(this, true));
	stream.Write(mClassId);
	write(stream);
}

void TownCenter::read(RakNet::BitStream & stream)
{
	stream.Read(mType);
	stream.Read(mLoc.x);
	stream.Read(mLoc.y);
	stream.Read(mLoc.z);
	stream.Read(mHealth);
}

void TownCenter::writeToFile(std::ofstream& of)
{
	of << "-------------" << std::endl;
	of << "Center" << std::endl;
	of << "Center Type: " << enumToString(mType) << std::endl;
	of << "Center Loc: ( " << std::to_string(mLoc.x) << ", " << std::to_string(mLoc.y) << ", " << std::to_string(mLoc.z) << " )" << std::endl;
	of << "Center Health: " << std::to_string(mHealth) << std::endl;
}

std::string TownCenter::enumToString(MonsterType monster)
{
	switch (monster)
	{
	case WEREWOLVES:
	{
		return "Werewolves";
	}
	break;
	case ELVES:
	{
		return "Elves";
	}
	break;
	case VAMPIRES:
	{
		return "Vampires";
	}
	break;
	case ORCS:
	{
		return "Orcs";
	}
	break;
	default:
	{
		return "Invalid";
	}
	break;
	}
}
