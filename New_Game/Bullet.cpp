#include "stdafx.h"
#include "Bullet.h"

void Bullet::initVariables()
{
}

void Bullet::initComponents()
{

}

Bullet::Bullet(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 4.f, 4.f);
	this->createMovementComponent(500.f, 450.f, 0.f, 0.f, 0, false);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("BULLET", 20.f, 0, 0, 0, 0, 4, 4);
}

Bullet::~Bullet()
{

}

void Bullet::updateAnimation(const float& dt)
{
		this->animationComponent->play("BULLET", dt);
}

void Bullet::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}
