#include "Music.h"
#include <iostream>

/*	Constructors/Destructor
* * * * * * * * * * * * */
Music::Music()
{
	mMusic = new sf::Music;
	mAssetName = "";
	mPlaymode = mOnce;

	initPlaymode(mPlaymode);
}

Music::Music(std::string assetName)
{
	mMusic = new sf::Music;
	mAssetName = assetName;
	mPlaymode = mOnce;

	std::string test = assetName;

	if (!mMusic->openFromFile(test.c_str()))
	{
		std::cout << "Cound not load!";
	}

	initPlaymode(mPlaymode);


}

Music::Music(float vol, std::string assetName, musicPlaymode playmode)
{
	mMusic = new sf::Music;
	mAssetName = assetName;
	mPlaymode = playmode;
	mVolume = vol;

	std::string test = assetName;

	if (!mMusic->openFromFile(test.c_str()))
	{
		std::cout << "Cound not load!";
	}

	initPlaymode(mPlaymode);
	mMusic->setVolume(vol);

}

Music::Music(const Music& other)
{
	mAssetName = other.mAssetName;	

	std::string test = mAssetName;

	if (!mMusic->openFromFile(test.c_str()))
	{
		std::cout << "Cound Not Load!";
	}

	initPlaymode(other.mPlaymode);
}

Music::~Music()
{
	mMusic->pause();
	//mMusic->stop();
	delete mMusic;
	mMusic = NULL;
}


void Music::play()
{
	//mMusic->setLoop(true);
	mMusic->play();
}