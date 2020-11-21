#include "Player.h"

void Player::initVariables()
{

}

void Player::initComponents()
{
	this->createMovementComponent(200.f, 50.f, 10.f);
}

Player::Player(float x, float y, sf::Texture& texture)
{
	this->initVariables();
	this->initComponents();

	this->setTexture(texture);
	this->setPosition(x, y);
}

Player::~Player()
{

}
