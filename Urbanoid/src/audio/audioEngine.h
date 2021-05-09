#pragma once
#include <string>
#include <irrKlang.h>
#include <unordered_map>

using namespace irrklang;

class AudioEngine {
public:
	struct Audio {
		bool WasPlayed = false;
	};

private:

	std::unordered_map<std::string, Audio*> m_Audios;
	ISoundEngine* m_Engine;

public:
	
	
	AudioEngine();
	~AudioEngine();

	void loadAudio(const unsigned int id, const std::string& name);

	ISound* play(const std::string& name, bool looped = false, bool startPaused = false, bool track = true);
	void playWithPause(const std::string& name, bool looped = false, bool startPaused = false, bool track = true);
	void playBgMusic(const std::string& name);
	void clearState();
	void stopAll() const;

	bool wasPlayed(const std::string& name) const;
};
