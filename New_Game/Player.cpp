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
	
	this->setTexture(texture_sheet);
	this->setPosition(x, y);

	this->createMovementComponent(400.f, 100.f, 50.f);
	this->createAnimationComponent(this->sprite, texture_sheet);

	this->animationComponent->addAnimation("IDLE_LEFT", 100.f, 1, 1, 7, 1, 36, 36);
}

Player::~Player()
{

}
