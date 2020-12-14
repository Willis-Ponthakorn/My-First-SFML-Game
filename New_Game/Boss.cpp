#include "stdafx.h"
#include "Boss.h"

void Boss::initVariables()
{
}

void Boss::initComponents()
{
}

Boss::Boss(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 26.25f, 28.f, 87.5f, 294.f);
	this->createMovementComponent(50.f, 2.f, 1.f, 0.f, 0, false);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("MOVING", 5.f, 0, 0, 3, 0, 80, 186);

	this->sprite.setOrigin(80.f, 0.f);
	this->sprite.setScale(-1.75f, 1.75f);
}

Boss::~Boss()
{
}

void Boss::updateAnimation(const float& dt)
{
	this->animationComponent->play("MOVING", dt);
}

void Boss::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Boss::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}
