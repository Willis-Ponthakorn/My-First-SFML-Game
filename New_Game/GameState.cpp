#include "stdafx.h"
#include "GameState.h"

void GameState::initVariables()
{
	this->camPosX = 0.f;
	this->camPosY = 0.f;
	this->mapPosXLeft = 0.f;
	this->mapPosYUp = 0.f;
	this->mapPosXRight = 0.f;
	this->mapPosYDown = 0.f;
}

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gSettings->resolution.width, 
		this->stateData->gSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(
		0,
		0,
		this->stateData->gSettings->resolution.width,
		this->stateData->gSettings->resolution.height)
	);
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gSettings->resolution.width),
			static_cast<float>(this->stateData->gSettings->resolution.height)
		)
	);
	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gSettings->resolution.width) / 2.f,
			static_cast<float>(this->stateData->gSettings->resolution.height) / 2.f
		)
	);
}

void GameState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->bgTexture.loadFromFile("res/image/background.png"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->bgTexture);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();

}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Font.ttf"))
	{
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_FONT";
	}
}

void GameState::initTexture()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("res/image/mainCharacterResize2.png"))
	{
		throw "ERROR::GAMESTATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["BULLET"].loadFromFile("res/image/Bullet.png"))
	{
		throw "ERROR::GAMESTATE::COULD_NOT_LOAD_BULLET_TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 520.f, "Leave");
}

void GameState::initPlayer()
{
	this->player = new Player(100, 600, this->textures["PLAYER_SHEET"]);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 330, 220, "res/image/Tileset3.png");
	this->tileMap->loadFromFile("text.eosmp");
}

GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initBackground();
	this->initKeybinds();
	this->initFonts();
	this->initTexture();
	this->initPauseMenu();

	this->initPlayer();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->tileMap;
}

void GameState::updateView(const float& dt)
{
	this->mapPosXLeft = this->camPosX * this->stateData->gSettings->resolution.width;
	this->mapPosYUp = this->camPosY * this->stateData->gSettings->resolution.height;
	this->mapPosXRight = (this->camPosX + 1.f) * this->stateData->gSettings->resolution.width;
	this->mapPosYDown = (this->camPosY + 1.f) * this->stateData->gSettings->resolution.height;
	//Cam move right
	if (this->player->getPosition().x > this->mapPosXRight)
	{
		this->view.move(static_cast<float>(this->stateData->gSettings->resolution.width), 0.f);
		camPosX++;
	}
	//Cam move left
	if (this->player->getPosition().x < this->mapPosXLeft)
	{
		this->view.move(static_cast<float>(this->stateData->gSettings->resolution.width) * -1.f, 0.f);
		camPosX--;
	}
	//Cam move up
	if (this->player->getPosition().y < this->mapPosYUp)
	{
		this->view.move(0.f, static_cast<float>(this->stateData->gSettings->resolution.height) * -1.f);
		camPosY--;
	}
	//Cam move down
	if (this->player->getPosition().y > this->mapPosYDown)
	{
		this->view.move(0.f, static_cast<float>(this->stateData->gSettings->resolution.height));
		camPosY++;
	}
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SHOOT"))))
		this->player->updateAttack();
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT") && this->getKeytime())
		this->endState();
}

void GameState::updateBackgroundPosition(float pos_x, float pos_y)
{
	this->background.setPosition(pos_x, pos_y);
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->player, dt);
}

void GameState::update(const float& dt)
{
	this->updateMousePosition(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused)
	{
		this->updateBackgroundPosition(this->mapPosXLeft, this->mapPosYUp);

		this->updateView(dt);

		this->updatePlayerInput(dt);
		
		this->updateTileMap(dt);
		
		this->player->update(dt);	
	}
	else
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	
	this->renderTexture.clear();

	this->renderTexture.setView(this->view);

	this->renderTexture.draw(this->background);

	this->tileMap->render(this->renderTexture, this->player->getGridPosition(static_cast<int>(this->stateData->gridSize)));

	this->player->render(this->renderTexture);

	this->tileMap->renderDeferred(this->renderTexture);

	if (this->paused)
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
