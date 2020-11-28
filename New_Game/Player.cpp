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
	this->createMovementComponent(400.f, 100.f, 50.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 1, 0, 36, 36);
	this->animationComponent->addAnimation("MOVING", 10.f, 0, 1, 6, 1, 36, 36);
}

Player::~Player()
{

}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if(this->movementComponent->getState(MOVING))
		this->animationComponent->play("MOVING", dt);

	this->hitboxComponent->update();
}
