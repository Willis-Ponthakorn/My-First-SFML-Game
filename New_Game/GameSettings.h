#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

class GameSettings
{
public:
	GameSettings();

	std::string title;
	sf::VideoMode resolution;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};

#endif
