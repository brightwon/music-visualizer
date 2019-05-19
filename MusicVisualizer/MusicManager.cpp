#include "MusicManager.h"

MusicManager::MusicManager() : windowSize(1024)
{
	init();
}

MusicManager::~MusicManager() {
	if (sound) {
		channel->removeDSP(dsp);
		sound->release();
	}

	if (fmodSystem) {
		dsp->release();
		fmodSystem->close();
		fmodSystem->release();
	}
}


void MusicManager::init() {
	FMOD_RESULT result = FMOD::System_Create(&fmodSystem);
	if (result != FMOD_OK) {
		printf("FMOD Error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
	else {
		fmodSystem->init(12, FMOD_INIT_NORMAL, NULL);
		fmodSystem->getMasterChannelGroup(&channelGroup);

		fmodSystem->createDSPByType(FMOD_DSP_TYPE_FFT, &dsp);
		dsp->setParameterInt(FMOD_DSP_FFT_WINDOWTYPE, FMOD_DSP_FFT_WINDOW_TRIANGLE);
		dsp->setParameterInt(FMOD_DSP_FFT_WINDOWSIZE, windowSize);
	}
}

void MusicManager::loadMusic(std::string filePath) {
	fmodSystem->createSound(filePath.c_str(), FMOD_LOOP_NORMAL | FMOD_CREATESAMPLE, 0, &sound);
}

void MusicManager::playMusic() {
	fmodSystem->playSound(sound, 0, false, &channel);
}

void MusicManager::update() {
	fmodSystem->update();
}

void MusicManager::initSpectrum() {
	fmodSystem->createDSPByType(FMOD_DSP_TYPE_FFT, &dsp);

	dsp->setParameterInt(FMOD_DSP_FFT_WINDOWTYPE, FMOD_DSP_FFT_WINDOW_HANNING);
	dsp->setParameterInt(FMOD_DSP_FFT_WINDOWSIZE, 2048);

	channelGroup->addDSP(0, dsp);
	dsp->setActive(true);
}

float MusicManager::getFrequency() {
	void *data;
	unsigned int length;
	dsp->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, &data, &length, 0, 0);

	FMOD_DSP_PARAMETER_FFT* fft = (FMOD_DSP_PARAMETER_FFT*)data;

	if (fft)
	{
		for (int channel = 0; channel < fft->numchannels; channel++)
		{
			for (int bin = 0; bin < fft->length; bin++)
			{
				float val = fft->spectrum[channel][bin];
				printf("%f\n", val);
			}
		}
	}

	return 0;
}
