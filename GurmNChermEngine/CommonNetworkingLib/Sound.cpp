#include "Sound.h"
#include <iostream>

/*	Constructors/Destructor
* * * * * * * * * * * * */
Sound::Sound()
{
	mAssetName = "";
	mPlaymode = Once;

	initPlaymode(mPlaymode);
}

Sound::Sound(std::string assetName)
{
	mAssetName = assetName;
	mPlaymode = Once;

	initPlaymode(mPlaymode);


}

void Sound::loadFromFile(std::string file)
{
	mAssetName = file;
	if (!mBuff.loadFromFile(file.c_str()))
	{
		std::cout << "Could not load!";
	}
	
	mSound.setBuffer(mBuff);

	//mSound.play();

}

void Sound::LoadFromFile()
{
	if (!mBuff.loadFromFile(mAssetName.c_str()))
	{
		std::cout << "Could not load!";
	}

	mSound.setBuffer(mBuff);
}

Sound::Sound(float vol, std::string assetName, Playmode playmode)
{
	mAssetName = assetName;
	mPlaymode = playmode;
	mVolume = vol;

	initPlaymode(mPlaymode);


}

Sound::Sound(const Sound& other)
{
	mAssetName = other.mAssetName;
	loadFromFile(mAssetName);

	initPlaymode(other.mPlaymode);
}

Sound::~Sound()
{
	mSound.pause();
	//mMusic->stop();
}


void Sound::play()
{
	//mMusic->setLoop(true);

	LoadFromFile();
	

	mSound.play();
}