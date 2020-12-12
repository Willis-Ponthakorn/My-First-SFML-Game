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
    sf::Music music;

    sf::SoundBuffer soundshoot;
    sf::SoundBuffer soundjump1;
    sf::SoundBuffer soundjump2;

    sf::Sound shooteffect;
    sf::Sound jump1effect;
    sf::Sound jump2effect;

    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::Font font;
    PauseMenu* pmenu;

    Player* player;
    std::vector<Bullet*> bullets;

    sf::Texture texture;

    TileMap* tileMap;

    float camPosX;
    float camPosY;
    float mapPosXLeft;
    float mapPosYUp;
    float mapPosXRight;
    float mapPosYDown;

    sf::Vector2f checkpointPlayer;

    void initVariables();
    void initDeferredRender();
    void initView();
    void initSound();
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
    void updateBullet(const float& dt);
    void updateTileMap(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

#endif
