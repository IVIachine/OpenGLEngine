#ifndef _SOUND_H_
#define _SOUND_H_

#include <SFML/audio.hpp>

//class AudioSystem;
//class Resources;

enum Playmode
{
	Loop,
	Once
};

class Sound
{
private:
	/*	Variables
	* * * * * * * * * * * * */
	sf::SoundBuffer mBuff;
	sf::Sound mSound;

	float mVolume;
	//Could also have pitch!

	Playmode mPlaymode;

	std::string
		mAssetName;

	std::string
		mKey;

	/*	Private Functions
	* * * * * * * * * * * * */
	void initPlaymode(Playmode playmode)
	{
		switch (playmode)
		{

		case Loop:
			mSound.setLoop(true);

		case Once:
			mSound.setLoop(false);

			// Default to once
		default:
			mSound.setLoop(false);
		}
	}

public:

	friend class AudioSystem;
	friend class Resources;

	void play();

	void loadFromFile(std::string file);
	void LoadFromFile();

	void pauseSound(){ mSound.pause(); };

	void stopSound(){ mSound.stop(); }

	void setKey(std::string key){ mKey = key; };

	std::string toString(){ return mAssetName; };

	std::string setKey(){ return mKey; };

	/*	Constructors/Destructor
	* * * * * * * * * * * * */
	Sound();

	Sound(std::string assetName);

	Sound(
		float vol,
		std::string assetName,
		Playmode playmode);

	Sound(const Sound& other);

	~Sound();




};

#endif