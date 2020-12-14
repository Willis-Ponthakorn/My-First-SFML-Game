#ifndef ENTITY_H
#define ENTITY_H

#include "HitboxComponent.h"
#include "MovementComponent.h"	
#include "AnimationComponent.h"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;

class Entity
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();

	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration, const float jumpHeight, const int maxJumpCount, const bool canJump);
	void createAnimationComponent(sf::Texture& texture_sheet);

	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2i getGridPosition(const int gridSizeU) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;
	virtual bool getIntersects(const sf::FloatRect& frect) const;
	virtual bool getCanJump() const;
	virtual int getJumpCount() const;

	virtual void setPosition(const float x, const float y);
	
	virtual void move(const float dir_x, const float dir_y, const float& dt);
	virtual void jump();
	virtual void checkpointJumpCount();
	virtual void resetJumpCount();
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = NULL;
};
#endif
