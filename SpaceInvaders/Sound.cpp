#include "Sound.h"

Sound::Sound()
{
}

Sound::~Sound()
{
}

void Sound::Play(const std::string& file)
{
	buffer.loadFromFile(file);
	sound.setBuffer(buffer);
	sound.play();
}