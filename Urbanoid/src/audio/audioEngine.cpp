#include "audioEngine.h"

#include <iostream>


#include "../../res/resource.h"

AudioEngine::AudioEngine()
	: m_Audios(std::unordered_map<std::string, Audio*>()), m_Engine(createIrrKlangDevice())
{

}

void AudioEngine::loadAudio(const unsigned int id, const std::string& name) {
	if (m_Audios.find(name) != m_Audios.end()) {
		return;
	}
	const Resource res = Resource(id, "AUDIO");
	std::string str = std::string(res.GetResourceString());

	m_Engine->addSoundSourceFromMemory((void*)str.c_str(), res.GetResourceString().size(), name.c_str());
	m_Audios[name] = new Audio{};
}

AudioEngine::~AudioEngine() {
	m_Engine->drop();
	m_Engine = nullptr;
}

ISound* AudioEngine::play(const std::string& name, bool looped, bool startPaused, bool track) {
	m_Audios.at(name)->WasPlayed = true;
	return m_Engine->play2D(name.c_str(), looped, startPaused, track);
}

void AudioEngine::playWithPause(const std::string& name, bool looped, bool startPaused, bool track) {
	ISound* sound = play(name, looped, startPaused, track);
	while (!sound->isFinished()) {
		// do nothing
	}
}

void AudioEngine::clearState() {
	for (auto [name, audio] : m_Audios) {
		audio->WasPlayed = false;
	}
}

void AudioEngine::stopAll() const {
	m_Engine->stopAllSounds();
}

bool AudioEngine::wasPlayed(const std::string& name) const {
	return m_Audios.at(name)->WasPlayed;
}
