#ifndef HIGHSCORESTATE_H
#define HIGHSCORESTATE_H

#define _CRT_SECURE_NO_WARNINGS

#include "State.h"
#include "Gui.h"

using namespace sf;

class sf::View;
class sf::Font;
class sf::RenderTexture;

class HighscoreState :
    public State
{
private:
    sf::View view;
    sf::RenderTexture renderTexture;

    sf::Text text;

    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::RectangleShape container;

    sf::Font font;

    std::map<std::string, gui::Button*> buttons;

    std::string sname;
    int sscore;

    int score[6] = {};
    std::string name[6] = {};
    char temp[255] = {};

    std::vector <std::pair<int, std::string>> userScore;

    std::FILE* fp;

    std::string str_hour;
    std::string str_min;
    std::string str_sec;

    bool comp(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b);

    void initVariables();
    void initBackground();
    void initFonts();
    void initButton();
    void initText();
    void initKeybinds();
    void readFile();
    void showHighScore(float x, float y, std::string word, sf::RenderTarget* target);

public:
    HighscoreState(StateData* state_data);
    virtual ~HighscoreState();

    void updateInput(const float& dt);
    void updateButtons();
    
    void updateHighScore();
    void update(const float& dt);
    
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif

