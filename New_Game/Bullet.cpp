#include "stdafx.h"
#include "Bullet.h"

void Bullet::initVariables()
{
	bullet.setSize(sf::Vector2f(2.f, 2.f));
	bullet.setFillColor(sf::Color(32, 32, 32, 255));
}

void Bullet::initComponents()
{
	
}

Bullet::Bullet(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 4.f, 4.f);
	this->createMovementComponent(250.f, 62.f, 31.f);
	this->createAnimationComponent(texture_sheet);
	
}

Bullet::~Bullet()
{
}

void Bullet::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->hitboxComponent->update();
}

void Bullet::render(sf::RenderWindow& target)
{
	target.draw(this->bullet);

	this->hitboxComponent->render(target);
}
