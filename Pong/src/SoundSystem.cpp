#include "SoundSystem.h"

#include <spdlog/spdlog.h>

void SoundSystem::Init() {
	spdlog::info("Initializing SoundSystem");
	m_Engine = irrklang::createIrrKlangDevice();
	if (!m_Engine) {
		spdlog::critical("Failed to initialize sound engine");
	}
	blip = AddSound("Sounds/blip.wav");
	score = AddSound("Sounds/score.mp3");
}

irrklang::ISoundSource* SoundSystem::AddSound(const std::string& path) {
	irrklang::ISoundSource* source;
	source = m_Engine->addSoundSourceFromFile(path.c_str());
	if (!source) {
		spdlog::critical("Failed to load sound ({})", path);
	}
	return source;
}

void SoundSystem::PlaySound(irrklang::ISoundSource* source) {
	m_Engine->play2D(source, false, false);
}

void SoundSystem::Close() {
	spdlog::info("Closing SoundSystem");
	m_Engine->drop();
}