#include "stdafx.h"
#include "Game.h"


void Game::initVariables()
{
	this->window = nullptr;

	this->dt = 0.f;

	this->gridSize = 32.f;
}

void Game::initGameSettings()
{
	this->gSettings.loadFromFile("Config/game_setting.ini");
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(
		this->gSettings.resolution,
		this->gSettings.title,
		sf::Style::Titlebar | sf::Style::Close,
		this->gSettings.contextSettings);

	this->window->setFramerateLimit(this->gSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gSettings.verticalSync);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();

	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.gSettings = &this->gSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}

Game::Game()
{
	this->initVariables();
	this->initGameSettings();
	this->initVariables();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Game::endApplication()
{
	std::cout << "Ending Application" << "\n";
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
	if (dt > 1.0f / 20.0f)
		dt = 1.0f / 20.0f;

}

void Game::pollEvent()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
		{
			this->window->close();
		}
	}
}

void Game::update()
{
	this->pollEvent();

	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->update(this->dt);

			if (this->states.top()->getQuit())
			{
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}

