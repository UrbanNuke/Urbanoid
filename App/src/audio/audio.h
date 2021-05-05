#pragma once
#include <string>
#include <irrKlang.h>

using namespace irrklang;

class Audio {
	
	std::string m_Name;
	ISoundEngine* m_Engine;

public:
	Audio(const unsigned int id, const std::string& name);
	~Audio();

	void play2D(bool looped = false) const;
	
};

