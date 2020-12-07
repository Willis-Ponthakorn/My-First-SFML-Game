#ifndef GUI_H
#define GUI_H

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<sstream>
#include<vector>

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED };

namespace gui
{
	class Button
	{
	private:
		short unsigned buttonState;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;



	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
		~Button();

		const bool isPressed() const;
		const std::string& getText() const;

		void setText(const std::string text);

		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;

		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;

	public:
		DropDownList(float x, float y, float width, float height, 
			sf::Font& font, std::string list[], 
			unsigned nrOfElements, unsigned default_index = 0);
		~DropDownList();
		
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);
	};
}
#endif

