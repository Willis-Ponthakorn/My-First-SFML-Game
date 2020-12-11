#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,
	float maxVelocity, float acceleration, float deceleration, float jumpHeight, int maxJumpCount, bool canJump)
	: sprite(sprite),
	maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
	this->jumpHeight = jumpHeight;
	this->maxJumpCount = maxJumpCount;
	this->jumpCount = 0;
	this->canJump = canJump;
	this->jumping = canJump;
}

MovementComponent::~MovementComponent()
{

}

const bool& MovementComponent::getCanJump() const
{
	return this->canJump;
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

void MovementComponent::resetJumpCount()
{
	this->jumpCount = 0;
}

void MovementComponent::stopVelocity()
{
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	this->velocity.y = 0.f;
}

void MovementComponent::jump()
{
	if (getCanJump())
	{
		this->velocity.y = -sqrtf(2.0f * 490.5f * jumpHeight);
		this->jumpCount++;
	}
}

void MovementComponent::move(const float dir_x, const float& dt)
{
	this->velocity.x += this->acceleration * dir_x;
}

void MovementComponent::update(const float& dt)
{
	if (jumpCount < maxJumpCount)
		canJump = true;
	else
		canJump = false;

	if (this->velocity.x > 0.f)
	{
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f)
	{
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (jumping && this->velocity.y <= 490.5f)
		this->velocity.y += 490.5f * dt;
	else if (jumping && this-> velocity.y > 490.5f)
		this->velocity.y = 490.5f;

	this->sprite.move(this->velocity * dt);
}
