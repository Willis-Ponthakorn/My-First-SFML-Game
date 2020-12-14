#ifndef BOSSBULLET_H
#define BOSSBULLET_H

#include "Entity.h"

class Entity;

class BossBullet :
    public Entity
{
private:
    void initVariables();
    void initComponents();


public:
    BossBullet(float x, float y, sf::Texture& texture_sheet, short type);
    virtual ~BossBullet();

    void updateAnimation(const float& dt);
    void update(const float& dt);

    void render(sf::RenderTarget& target);
};

#endif

