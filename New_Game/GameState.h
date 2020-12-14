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
    sf::Music bossMusic;
    sf::Music endMusic;

    sf::SoundBuffer soundshoot;
    sf::SoundBuffer soundjump1;
    sf::SoundBuffer soundjump2;
    sf::SoundBuffer soundcheckpoint;
    sf::SoundBuffer sounddeath;
    sf::SoundBuffer soundwarp;
    sf::SoundBuffer soundbosssound;
    sf::SoundBuffer soundbosshurt;
    sf::SoundBuffer soundbossdie;

    sf::Sound shooteffect;
    sf::Sound jump1effect;
    sf::Sound jump2effect;
    sf::Sound checkpointeffect;
    sf::Sound deatheffect;
    sf::Sound warpeffect;
    sf::Sound bosssoundeffect;
    sf::Sound bosshurteffect;
    sf::Sound bossdieeffect;

    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Text text;
    sf::Clock clock;
    sf::Clock bossTiming;
    sf::Time gameTime;

    sf::Texture bgTexture;
    sf::Texture bgBossTexture;
    sf::RectangleShape background;
    sf::RectangleShape bossBackground;
    sf::RectangleShape bossHP;
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
    bool getInBossStage;
    bool getWin;
    std::vector<bool> moveMonsterRight;
    float camPosX;
    float camPosY;
    float mapPosXLeft;
    float mapPosYUp;
    float mapPosXRight;
    float mapPosYDown;
    int jumpRandom;
    int sec;
    int checkSec;
    float textPos;
    float bossMaxHP;
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
    void initText();
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
    void updateTime();
    void updatePlayer(const float& dt);
    void updateMonster(const float& dt);
    void updateItem(const float& dt);
    void updateBoss(const float& dt);
    void updateBossHP();
    void updatePauseMenuButtons();
    void updateMusic();
    void updateBackgroundPosition(float pos_x, float pos_y);
    void updateBullet(const float& dt);
    void updateTileMap(const float& dt);
    void updateBossStage(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

#endif
