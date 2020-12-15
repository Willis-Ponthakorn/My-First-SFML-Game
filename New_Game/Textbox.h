#ifndef TEXTBOX_H
#define TEXTBOX_H

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

#include "Gui.h"

class Gui;

class Textbox
{
private:
	sf::Font& font;
	sf::Text textbox;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

	std::ostringstream text;
	bool getWin = false;
	bool isselected = false;
	bool haslimit = false;
	unsigned limit;

	void inputLogic(int chartyped);
	void deleteLastchar();

public:
	Textbox();
	Textbox(int size, sf::Color color, bool sel, sf::RenderWindow& window, sf::Font& font);

	~Textbox();

	std::map<std::string, gui::Button* >& getButtons();

	const bool isButtonPressed(const std::string key);
	const bool getWinStatus() const;
	void addButton(const std::string key, float y, const std::string text);

	void setPosition(sf::Vector2f pos);

	void setGetWin(bool getWind);
	void setlimit(bool ToF);
	void setlimit(bool ToF, int lim);
	void setSelected(bool sel);
	std::string gettext();
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
	void typeOn(int input);
};

#endif