#ifndef _MUSIC_H_
#define _MUSIC_H_

// GurmLib
//#include "System.h"

//Allegro ADD TO SYSTEM LATER PERHAPS
//#include <SFML/audio.hpp>
#include <SFML/Audio/Music.hpp>


//class AudioSystem;
//class Resources;

enum musicPlaymode
{
	mLoop,
	mOnce
};

class Music
{
private:
	/*	Variables
	* * * * * * * * * * * * */
	sf::Music* mMusic;
	
	float mVolume;
	//Could also have pitch!

	musicPlaymode mPlaymode;
	
	std::string
		mAssetName;

	std::string
		mKey;
	
	/*	Private Functions
	* * * * * * * * * * * * */
	void initPlaymode(musicPlaymode playmode)
	{
		switch (playmode)
		{

			case mLoop:
				mMusic->setLoop(true);

			case mOnce:
				mMusic->setLoop(false);

			// Default to once
			default:
				mMusic->setLoop(false);
		}
	}

public:
	/*	Constructors/Destructor
	* * * * * * * * * * * * */
	Music();

	Music(std::string assetName);

	Music(
		float vol,
		std::string assetName,
		musicPlaymode playmode);

	Music(const Music& other);

	~Music();

	friend class AudioSystem;
	friend class Resources;

	void setVol(float newVol) { mMusic->setVolume(newVol); };

	void play();
	
	void pauseSound(){ mMusic->pause(); };

	void stopMusic(){ mMusic->stop(); }

	void setKey(std::string key){ mKey = key; };

	std::string toString(){ return mAssetName; };

	std::string setKey(){ return mKey; };


};

#endif