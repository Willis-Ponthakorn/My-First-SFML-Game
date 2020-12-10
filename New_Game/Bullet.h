#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet:
	public Entity
{
private:
	sf::RectangleShape bullet;

	void initVariables();
	void initComponents();

	
public:
	Bullet(float x, float y, sf::Texture& texture_sheet);
	virtual ~Bullet();

	float getRight();
	float getLeft();
	float getTop();
	float getBottom();

	void shoot(float speed);

	void update(const float& dt);
	void render(sf::RenderWindow& target);
};

#endif

