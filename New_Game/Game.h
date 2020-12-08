#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	GameSettings gSettings;
	sf::RenderWindow* window;
	sf::Event event;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	void initVariables();
	void initGameSettings();
	void initWindow();
	void initKeys();
	void initStates();


public:
	Game();
	virtual ~Game();

	const bool getWindowIsOpen() const;

	void endApplication();

	void updateDt();
	void pollEvent();
	void update();
	void render();
	void run();
};
#endif


