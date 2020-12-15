#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initVariables()
{
	this->inMainMenuState = true;
	this->toggleEditor = false;
}

void MainMenuState::initSound()
{
	this->music.openFromFile("res/sound/MainMenu.wav");
	this->music.setVolume(25);

	this->music.setLoop(true);
	this->music.play();
}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->bgTexture.loadFromFile("res/image/gameBackground3.png"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->bgTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Font.ttf"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_FONT";
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new gui::Button(465.f, 270.f, 150.f, 50.f,
		&this->font, "New Game", 20,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["SCOREBOARD_STATE"] = new gui::Button(465.f, 370.f, 150.f, 50.f,
		&this->font, "Scoreboard", 20,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	/*this->buttons["EDITOR_STATE"] = new gui::Button(465.f, 470.f, 150.f, 50.f,
		&this->font, "Editor", 20,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));*/

	this->buttons["EXIT_STATE"] = new gui::Button(465.f, 570.f, 150.f, 50.f,
		&this->font, "Leave", 20,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initSound();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

const bool MainMenuState::getInMainMenuState() const
{
	return this->inMainMenuState;
}

void MainMenuState::updateInput(const float& dt)
{
}

void MainMenuState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}
	
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->music.stop();
		this->nowOutMainMenuState();
		this->states->push(new GameState(this->stateData));
	}

	if (this->buttons["SCOREBOARD_STATE"]->isPressed())
	{
		this->states->push(new HighscoreState(this->stateData));
	}

	/*if (this->buttons["EDITOR_STATE"]->isPressed() && this->toggleEditor)
	{
		this->music.stop();
		this->nowOutMainMenuState();
		this->states->push(new EditorState(this->stateData));
	}*/

	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	if(this->music.getStatus() == 0 && this->getInMainMenuState())
		this->music.play();

	this->updateMousePosition();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);
}

