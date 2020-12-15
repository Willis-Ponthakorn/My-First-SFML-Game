#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "EditorState.h"
#include "HighscoreState.h"
#include "Gui.h"

class MainMenuState :
    public State
{
private:
    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;

    sf::Music music;

    bool inMainMenuState;
    bool toggleEditor;

    void initVariables();
    void initSound();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    const bool getInMainMenuState() const;

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};
#endif

