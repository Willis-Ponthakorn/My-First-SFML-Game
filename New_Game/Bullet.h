#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Entity;

class Bullet :
	public Entity
{
private:
	void initVariables();
	void initComponents();

	
public:
    Bullet(float x, float y, sf::Texture& texture_sheet);
    virtual ~Bullet();

	void updateAnimation(const float& dt);
    void update(const float& dt);

    void render(sf::RenderTarget& target);
};

#endif

