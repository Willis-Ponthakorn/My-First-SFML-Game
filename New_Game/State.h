#ifndef  STATE_H
#define STATE_H

#include "Player.h"
#include "Bullet.h"
#include "Monster.h"
#include "Item.h"
#include "Boss.h"
#include "BossBullet.h"
#include "GameSettings.h"
#include "Textbox.h"

class Player;
class Bullet;
class Monster;
class Item;
class Boss;
class BossBullet;
class GameSettings;
class State;

class StateData
{
public:
	StateData() {};

	float gridSize;
	sf::RenderWindow* window;
	GameSettings* gSettings;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
};

class State
{
private:


protected:
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	bool inMainMenuState;
	float keytime;
	float keytime1;
	float keytime2;
	float keytime3;
	float keytimeMax;
	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

	std::map<std::string, sf::Texture> textures;

	virtual void initKeybinds() = 0;

public:
	State(StateData* state_data);
	virtual ~State();

	const bool& getInMainMenuState() const;
	const bool& getQuit() const;
	const bool getKeytime();
	const bool getKeytime1();
	const bool getKeytime2();
	const bool getKeytime3();

	void nowInMainMenuState();
	void nowOutMainMenuState();
	void endState();
	void pauseState();
	void unpauseState();
	
	virtual void updateMousePosition(sf::View* view = NULL);
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};
#endif

