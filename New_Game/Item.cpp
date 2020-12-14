#include "stdafx.h"
#include "Item.h"

void Item::initVariables()
{
}

void Item::initComponents()
{
}

Item::Item(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 20.f, 20.f);
	this->createMovementComponent(0.f, 0.f, 0.f, 0.f, 0, false);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 20.f, 0, 0, 1, 0, 20, 21);
}

Item::~Item()
{
}

void Item::updateAnimation(const float& dt)
{
	this->animationComponent->play("IDLE", dt);
}

void Item::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Item::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}
