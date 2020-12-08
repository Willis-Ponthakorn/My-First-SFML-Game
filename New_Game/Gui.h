#ifndef GUI_H
#define GUI_H

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED };

namespace gui
{
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;



	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color outlineIdleColor = sf::Color::Transparent, sf::Color outlineHoverColor = sf::Color::Transparent, sf::Color outlineActiveColor = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();

		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		void setText(const std::string text);
		void setId(const short unsigned id);

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

		const unsigned short& getActiveElementId() const;
		
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);
	};
}
#endif

