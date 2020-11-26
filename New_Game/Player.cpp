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

	this->createMovementComponent(400.f, 100.f, 50.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 0, 6, 0, 36, 36);
}

Player::~Player()
{

}

void Player::update(const float& dt)
{
	Entity::update(dt);

	this->animationComponent->play("IDLE_LEFT", dt);
}
