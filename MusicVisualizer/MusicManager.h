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

	int initSpectrum(int maxBars);
	void getFrequency(float *spectrum);

private:
	FMOD::System *fmodSystem;
	FMOD::Channel *channel;
	FMOD::Sound *sound;
	FMOD::DSP *dsp;

	vector<int> numSamplesPerBar;
	int windowSize;
	void init();
};

#endif