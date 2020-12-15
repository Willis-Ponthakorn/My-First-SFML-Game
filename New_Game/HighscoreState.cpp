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
	/*std::ifstream in_file;

	in_file.open("./Score.txt");
	for (int i = 0; i < 5; i++)
	{
		in_file >> score[i] >> name[i];

		userScore.push_back(make_pair(score[i], name[i]));
		std::cout << temp << " " << score;
	}
	sort(userScore.begin(), userScore.end());
	in_file.close();

	std::cout << userScore.size() << "\n";*/

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

void HighscoreState::showHighScore(int x, int y, std::string word, sf::RenderTarget* target)
{
	text.setPosition(x, y);
	text.setString(word);
	if (word == "HIGHSCORE")
		text.setCharacterSize(60);
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

	this->renderButtons(*target);

	fp = fopen("Score.txt", "w");
	for (int i = 0; i < 5; i++)
	{

		strcpy(temp, userScore[i].second.c_str());
		fprintf(fp, "%s %d\n", temp, userScore[i].first);
	}
	fclose(fp);

	showHighScore(375, 130, "HIGHSCORE", target);

	for (int i = 0; i < 5; i++)
	{
		showHighScore(400, 190 + (1 + i) * 60, userScore[i].second, target);
		showHighScore(600, 190 + (1 + i) * 60, std::to_string(userScore[i].first), target);
	}
}
