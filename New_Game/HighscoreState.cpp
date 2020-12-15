#include "stdafx.h"
#include "HighscoreState.h"
#define _CRT_SECURE_NO_WARNINGS

bool HighscoreState::comp(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b)
{
	return (a.first > b.first);
}

void HighscoreState::initVariables()
{
	this->sname = "Unknown";
	this->sscore = 0;
}

void HighscoreState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 100));

	if (!this->bgTexture.loadFromFile("res/image/gameBackground.png"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->bgTexture);
}

void HighscoreState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Font.ttf"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_FONT";
	}
}

void HighscoreState::initButton()
{
	this->buttons["EXIT_STATE"] = new gui::Button(850.f, 640.f, 150.f, 50.f,
		&this->font, "Leave", 20,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

void HighscoreState::initText()
{
	this->text.setFont(this->font);
	this->text.setPosition(550, 150);
}

void HighscoreState::initKeybinds()
{
}

void HighscoreState::readFile()
{
	fp = fopen("Score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);

		userScore.push_back(make_pair(score[i], name[i]));
		std::cout << temp << " " << score;
	}
	sort(userScore.begin(), userScore.end());


	fclose(fp);
}

void HighscoreState::showHighScore(float x, float y, std::string word, sf::RenderTarget* target)
{
	text.setPosition(x, y);
	text.setString(word);
	if (word == "HIGHSCORE")
		text.setCharacterSize(80);
	else
		text.setCharacterSize(30);

	target->draw(this->text);
}

HighscoreState::HighscoreState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButton();
	this->initText();
	this->readFile();
}

HighscoreState::~HighscoreState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void HighscoreState::updateInput(const float& dt)
{

}

void HighscoreState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void HighscoreState::updateHighScore()
{

}

void HighscoreState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->updateButtons();
}

void HighscoreState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void HighscoreState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	target->draw(this->container);

	this->renderButtons(*target);

	fp = fopen("Score.txt", "w");
	for (int i = 0; i < 5; i++)
	{

		strcpy(temp, userScore[i].second.c_str());
		fprintf(fp, "%s %d\n", temp, userScore[i].first);
	}
	fclose(fp);

	showHighScore(340.f, 110.f, "HIGHSCORE", target);

	for (int i = 0; i < 5; i++)
	{
		int temp = userScore[i].first;
		int sec = temp % 60;
		temp /= 60;
		int minute = temp % 60;
		int hour = temp / 60;
		if (hour < 10)
			str_hour = "0" + std::to_string(hour);
		else
			str_hour = std::to_string(hour);

		if (minute < 10)
			str_min = "0" + std::to_string(minute);
		else
			str_min = std::to_string(minute);

		if (sec < 10)
			str_sec = "0" + std::to_string(sec);
		else
			str_sec = std::to_string(sec);

		std::string timeScore = str_hour + ":" + str_min + ":" + str_sec;
		showHighScore(340.f, 190.f + static_cast<float>(1 + i) * 60.f, userScore[i].second, target);
		showHighScore(600.f, 190.f + static_cast<float>(1 + i) * 60.f, timeScore, target);
	}
}
