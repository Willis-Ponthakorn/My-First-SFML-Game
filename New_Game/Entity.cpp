#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
}

void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration, const float jumpHeight, const int maxJumpCount, const bool canJump)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration, jumpHeight, maxJumpCount, canJump);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	return this->sprite.getPosition();
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
	if (this->hitboxComponent)
		return sf::Vector2i(
			static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI,
			static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI
		);

	return sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeI
	);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();

	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
	if(this->hitboxComponent && this->movementComponent)
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
	
	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

bool Entity::getIntersects(const sf::FloatRect& frect) const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->intersects(frect);

	return this->sprite.getGlobalBounds().intersects(frect);
}

bool Entity::getCanJump() const
{
	return this->movementComponent->getCanJump();
}

int Entity::getJumpCount() const
{
	return this->movementComponent->getJumpCount();
}

void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(x, y);
	else
		this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->move(dir_x, dir_y, dt);
}

void Entity::jump()
{
	if (this->movementComponent)
		this->movementComponent->jump();
}

void Entity::checkpointJumpCount()
{
	if (this->movementComponent)
		this->movementComponent->checkpointJumpCount();
}

void Entity::resetJumpCount()
{
	if (this->movementComponent)
		this->movementComponent->resetJumpCount();
}

void Entity::stopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}

void Entity::update(const float& dt)
{

}

void Entity::render(sf::RenderTarget& target)
{
}
