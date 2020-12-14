#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Item :
    public Entity
{
private:
    void initVariables();
    void initComponents();

public:
    Item(float x, float y, sf::Texture& texture_sheet);
    virtual ~Item();

    void updateAnimation(const float& dt);
    void update(const float& dt);

    void render(sf::RenderTarget& target);
};

#endif

