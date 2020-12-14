#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class PauseMenu;
class Player;
class Bullet;
class Item;
class Boss;
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
    sf::SoundBuffer soundcheckpoint;
    sf::SoundBuffer sounddeath;

    sf::Sound shooteffect;
    sf::Sound jump1effect;
    sf::Sound jump2effect;
    sf::Sound checkpointeffect;
    sf::Sound deatheffect;

    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::Font font;
    PauseMenu* pmenu;

    Player* player;
    std::vector<Bullet*> bullets;
    std::vector<Monster*> monsters;
    std::vector<Item*> items;
    Boss* boss;

    sf::Texture texture;

    TileMap* tileMap;

    bool moveBossUp;
    bool moveMonsterRight;
    float camPosX;
    float camPosY;
    float mapPosXLeft;
    float mapPosYUp;
    float mapPosXRight;
    float mapPosYDown;
    int jumpRandom;
    std::vector<sf::Vector2f> itemPos;
    std::vector<sf::Clock> itemTime;

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
    void initMonster();
    void initItem();
    void initBoss();
    void initTileMap();

public:
    GameState(StateData* state_data);
    virtual ~GameState();

    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePlayer(const float& dt);
    void updateMonster(const float& dt);
    void updateItem(const float& dt);
    void updateBoss(const float& dt);
    void updatePauseMenuButtons();
    void updateBackgroundPosition(float pos_x, float pos_y);
    void updateBullet(const float& dt);
    void updateTileMap(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

#endif
