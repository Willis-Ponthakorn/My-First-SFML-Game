#include "stdafx.h"
#include "Textbox.h"

Textbox::Textbox()
	: font(font)
{
}

Textbox::Textbox(int size, sf::Color color, bool sel, sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x) / 2.f,
			static_cast<float>(window.getSize().y) - 100.f
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		30.f
	);

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("Enter Your Name");
	this->menuText.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 40.f
	);

	this->textbox.setFont(font);
	this->textbox.setFillColor(color);
	this->textbox.setCharacterSize(size);
	
	
	this->isselected = sel;
	if (sel) {
		this->textbox.setString("_");
	}
	else {
		this->textbox.setString("");
	}
}

Textbox::~Textbox()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& Textbox::getButtons()
{
	return this->buttons;
}

const bool Textbox::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

const bool Textbox::getWinStatus() const
{
	return this->getWin;
}

void Textbox::addButton(const std::string key, float y, const std::string text)
{
	float width = 150.f;
	float height = 50.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(x, y, width, height,
		&this->font, text, 20,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

void Textbox::setPosition(sf::Vector2f pos)
{
	this->textbox.setPosition(pos);
}

void Textbox::setGetWin(bool getWin)
{
	this->getWin = getWin;
}

void Textbox::setlimit(bool ToF)
{
	this->haslimit = ToF;
}

void Textbox::setlimit(bool ToF, int lim)
{
	this->haslimit = ToF;
	this->limit = lim;
}

void Textbox::setSelected(bool sel)
{
	this->isselected = sel;
	if (!sel) {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i];
		}
		this->textbox.setString(newT);
	}
}

std::string Textbox::gettext()
{
	return this->text.str();
}

void Textbox::update(const sf::Vector2i& mousePosWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}

void Textbox::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->textbox);
	target.draw(this->menuText);
}

void Textbox::typeOn(int input)
{
	if (isselected) {
		if (input < 128) {
			if (haslimit) {
				if (text.str().length() <= limit) {
					inputLogic(input);
				}
				else if (text.str().length() > limit && input == DELETE_KEY) {
					deleteLastchar();
				}
			}
			else {
				inputLogic(input);
			}
		}
	}
}

void Textbox::inputLogic(int chartyped)
{
	if (chartyped != DELETE_KEY && chartyped != ENTER_KEY && chartyped != ESCAPE_KEY) {
		text << static_cast<char>(chartyped);
	}
	else if (chartyped == DELETE_KEY) {
		if (text.str().length() > 0) {
			deleteLastchar();
		}
	}
	this->textbox.setString(text.str() + "_");
}

void Textbox::deleteLastchar()
{
	std::string t = text.str();
	std::string newT = "";
	for (int i = 0; i < t.length() - 1; i++) {
		newT += t[i];
	}
	this->text.str("");
	this->text << newT;
	this->textbox.setString(text.str());
}
