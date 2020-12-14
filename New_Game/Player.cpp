#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{

}

void Player::initComponents()
{
	
}

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();
	
	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 32.f, 36.f);
	this->createMovementComponent(250.f, 62.f, 31.f, 100.f, 2, true);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 20.f, 0, 0, 1, 0, 36, 36);
	this->animationComponent->addAnimation("MOVING", 10.f, 0, 1, 6, 1, 36, 36);
}

Player::~Player()
{

}

void Player::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if(this->movementComponent->getState(MOVING))
		this->animationComponent->play("MOVING", dt);
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}
