#include "stdafx.h"
#include "Monster.h"

void Monster::initVariables()
{
	this->type = 0;
}

void Monster::initComponents()
{
}

Monster::Monster(float x, float y, sf::Texture& texture_sheet, short type)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 24.f, 25.f);
	this->createMovementComponent(150.f, 30.f, 15.f, 100.f, 1, true);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE_LEFT", 3.f, 0, 0, 7, 0, 30, 25);

	this->type = type;
}

Monster::~Monster()
{
}

const short& Monster::getType() const
{
	return this->type;
}

void Monster::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(IDLE))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->animationComponent->play("IDLE_LEFT", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(1.f, 1.f);
		this->animationComponent->play("IDLE_LEFT", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(24.f, 0.f);
		this->sprite.setScale(-1.f, 1.f);
		this->animationComponent->play("IDLE_LEFT", dt);
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("IDLE_LEFT", dt);
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("IDLE_LEFT", dt);
	}
	else if (this->movementComponent->getState(MOVING_UP) && this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->animationComponent->play("IDLE_LEFT", dt);
	}
	else if (this->movementComponent->getState(MOVING_UP) && this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(24.f, 0.f);
		this->sprite.setScale(-1.f, 1.f);
		this->animationComponent->play("IDLE_LEFT", dt);
	}
	else if (this->movementComponent->getState(MOVING_DOWN) && this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->animationComponent->play("IDLE_LEFT", dt);
	}
	else if (this->movementComponent->getState(MOVING_DOWN) && this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(24.f, 0.f);
		this->sprite.setScale(-1.f, 1.f);
		this->animationComponent->play("IDLE_LEFT", dt);
	}
}

void Monster::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Monster::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}
