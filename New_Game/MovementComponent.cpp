#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite),
	maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{

}

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0)
			return true;

		break;
	case MOVING:
		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;

		break;
	case MOVING_LEFT:
		if (this->velocity.x < 0.f)
			return true;

		break;
	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
			return true;

		break;
	case MOVING_UP:
		if (this->velocity.x < 0.f)
			return true;

		break;
	case MOVING_DOWN:
		if (this->velocity.y > 0.f)
			return true;

		break;
	}

	return false;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	this->velocity.x += this->acceleration * dir_x;

	if (this->velocity.x > 0.f)
	{
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;
	}
	else if (this->velocity.x < 0.f)
	{
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;
	}
	this->velocity.y += this->acceleration * dir_y;
	if (this->velocity.y > 0.f)
	{
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;
	}
	else if (this->velocity.y < 0.f)
	{
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;
	}


}

void MovementComponent::update(const float& dt)
{
	if (this->velocity.x > 0.f)
	{
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f)
	{
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}
	if (this->velocity.y > 0.f)
	{
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f)
	{
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}
	this->sprite.move(this->velocity * dt);
}
