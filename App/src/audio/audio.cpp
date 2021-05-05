#include "audio.h"

#include "../../res/resource.h"

Audio::Audio(const unsigned id, const std::string& name)
	: m_Name(name), m_Engine(nullptr)
{
	const Resource res = Resource(id, "AUDIO");
	std::string str = std::string(res.GetResourceString());

	m_Engine = createIrrKlangDevice();
	m_Engine->addSoundSourceFromMemory((void*)str.c_str(), res.GetResourceString().size(), name.c_str());
}

Audio::~Audio() {
	delete m_Engine;
}

void Audio::play2D(bool looped) const {
	m_Engine->play2D(m_Name.c_str(), looped);
}
