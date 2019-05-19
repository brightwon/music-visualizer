#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MusicManager
{
public:
	MusicManager();
	~MusicManager();

	void loadMusic(string filePath);
	void playMusic();
	void update();
	void initSpectrum();
	float getFrequency();

private:
	FMOD::System *fmodSystem;
	FMOD::Channel *channel;
	FMOD::ChannelGroup *channelGroup;
	FMOD::Sound *sound;
	FMOD::DSP *dsp;
	int windowSize;
	void init();
};

#endif