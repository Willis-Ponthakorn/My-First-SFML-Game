#include "stdafx.h"
#include "SettingState.h"

void SettingState::initVariables()
{

}

void SettingState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->bgTexture.loadFromFile("res/image/gameBackground.png"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->bgTexture);
}

void SettingState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Font.ttf"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_FONT";
	}
}

void SettingState::initKeybinds()
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

void SettingState::initGui()
{
	this->buttons["BACK"] = new gui::Button(390.f, 620.f, 150.f, 50.f,
		&this->font, "Back", 20,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["APPLY"] = new gui::Button(550.f, 620.f, 150.f, 50.f,
		&this->font, "Apply", 20,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	std::string li[] = { "0%","25%","50%","75%","100%" };
	this->dropDownLists["SOUND"] = new gui::DropDownList(100.f, 100.f, 150.f, 50.f, font, li, 5);
}

void SettingState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(100.f, 50.f));
	this->optionsText.setCharacterSize(40);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));


	this->optionsText.setString(
		"Volume \tVsync \t"
	);
}

SettingState::SettingState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}

SettingState::~SettingState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	
	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}

void SettingState::updateInput(const float& dt)
{

}

void SettingState::updateGui(const float& dt)
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	if (this->buttons["APPLY"]->isPressed())
	{
		this->window->create(this->stateData->gSettings->resolution, this->stateData->gSettings->title, sf::Style::Titlebar | sf::Style::Close);
	}

	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePosView, dt);
	}
}

void SettingState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->updateGui(dt);
}

void SettingState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);

	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}

