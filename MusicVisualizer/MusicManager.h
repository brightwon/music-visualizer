#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <string>
#include <fmod/fmod.hpp>

class MusicManager
{
public:
	MusicManager();
	~MusicManager();
	void loadSound(std::string filePath);
	void playSound();
	void pauseSound();

private:
	FMOD::System* musicSystem;
	FMOD::Channel* musicChannel;
	FMOD::Sound* musicSound;
	void init();
};

#endif