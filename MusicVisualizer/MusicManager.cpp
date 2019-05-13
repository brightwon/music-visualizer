#include "MusicManager.h"

#include <iostream>
#include <string>


MusicManager::MusicManager()
{
	init();
}


MusicManager::~MusicManager()
{
}

void MusicManager::init() {
	FMOD_RESULT result;
	result = FMOD::System_Create(&musicSystem);
	if (result != FMOD_OK) {
		printf("FMOD Create Error!");
		exit(-1);
	}

	result = musicSystem->init(1, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		printf("FMOD Initialize Error!");
		exit(-1);
	}
}

void MusicManager::loadSound(std::string filePath) {
	musicSystem->createSound(filePath.c_str(), FMOD_DEFAULT, NULL, &musicSound);
}

void MusicManager::playSound() {
	musicSystem->playSound(musicSound, NULL, false, NULL);
}

void MusicManager::pauseSound() {
	musicSystem->playSound(musicSound, NULL, true, NULL);
}