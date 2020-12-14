#include "stdafx.h"
#include "BossBullet.h"

void BossBullet::initVariables()
{
}

void BossBullet::initComponents()
{

}

BossBullet::BossBullet(float x, float y, sf::Texture& texture_sheet, short type)
{
	this->initVariables();

	this->setPosition(x, y);

	if (type == 1)
	{
		this->createHitboxComponent(this->sprite, 0.f, 0.f, 14.f, 14.f);
		this->createMovementComponent(500.f, 450.f, 0.f, 0.f, 0, false);
		this->createAnimationComponent(texture_sheet);

		this->animationComponent->addAnimation("BULLET", 3.f, 0, 0, 7, 0, 14, 14);
	}
	else if (type == 2)
	{
		this->createHitboxComponent(this->sprite, 2.f, 2.f, 28.f, 28.f);
		this->createMovementComponent(350.f, 300.f, 0.f, 0.f, 0, false);
		this->createAnimationComponent(texture_sheet);

		this->animationComponent->addAnimation("BULLET", 3.f, 0, 1, 6, 1, 32, 32);
	}
	else if (type == 3)
	{
		this->createHitboxComponent(this->sprite, 2.f, 2.f, 16.f, 16.f);
		this->createMovementComponent(200.f, 100.f, 0.f, 0.f, 0, false);
		this->createAnimationComponent(texture_sheet);

		this->animationComponent->addAnimation("BULLET", 3.f, 0, 4, 5, 4, 20, 20);
	}
	else if (type == 4)
	{
		this->createHitboxComponent(this->sprite, 8.f, 8.f, 44.f, 44.f);
		this->createMovementComponent(300.f, 250.f, 0.f, 0.f, 0, false);
		this->createAnimationComponent(texture_sheet);

		this->animationComponent->addAnimation("BULLET", 3.f, 0, 2, 7, 2, 76, 62);
	}
}

BossBullet::~BossBullet()
{

}

void BossBullet::updateAnimation(const float& dt)
{
	this->animationComponent->play("BULLET", dt);
}

void BossBullet::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void BossBullet::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}
