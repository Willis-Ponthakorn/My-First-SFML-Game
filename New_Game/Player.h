#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Bullet.h"

class Entity;

class Player :
    public Entity
{
private:
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    void updateAnimation(const float& dt);
    void update(const float& dt);

    void render(sf::RenderTarget& target);
};

#endif