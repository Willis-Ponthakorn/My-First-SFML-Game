#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class PauseMenu;
class Player;
class TileMap;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState :
    public State
{
private:
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::Font font;
    PauseMenu* pmenu;

    Player* player;
    Bullet* bullet;
    sf::Texture texture;

    TileMap* tileMap;

    float camPosX;
    float camPosY;
    float mapPosXLeft;
    float mapPosYUp;
    float mapPosXRight;
    float mapPosYDown;

    void initVariables();
    void initDeferredRender();
    void initView();
    void initBackground();
    void initKeybinds();
    void initFonts();
    void initTexture();
    void initPauseMenu();
    void initPlayer();
    void initTileMap();

public:
    GameState(StateData* state_data);
    virtual ~GameState();

    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseMenuButtons();
    void updateBackgroundPosition(float pos_x, float pos_y);
    void updateTileMap(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

#endif
