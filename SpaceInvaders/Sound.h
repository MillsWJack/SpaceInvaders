#pragma once
#include <SFML\\Audio.hpp>

class Sound
{
public:
	Sound();
	~Sound();

	void Play(const std::string& file);

private:

	sf::SoundBuffer buffer;
	sf::Sound sound;
};
