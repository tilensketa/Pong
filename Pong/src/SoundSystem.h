#pragma once

#include <irrKlang/irrKlang.h>
#include <string>

class SoundSystem {
public:
	void Init();
	irrklang::ISoundSource* AddSound(const std::string& path);
	void PlaySound(irrklang::ISoundSource* source);
	void Close();
private:
	irrklang::ISoundEngine* m_Engine;
public:
	irrklang::ISoundSource* blip;
	irrklang::ISoundSource* score;
};