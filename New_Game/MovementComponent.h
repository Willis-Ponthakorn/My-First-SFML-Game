#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent
{
private:
	sf::Sprite& sprite;
	
	float maxVelocity;
	float acceleration;
	float deceleration;
	bool canJump;
	bool jumping;
	float jumpHeight;
	int jumpCount;
	int maxJumpCount;

	sf::Vector2f velocity;

public:
	MovementComponent(sf::Sprite& sprite, 
		float maxVelocity, float acceleration, float deceleration, float jumpHeight, int maxJumpCount, bool canJump);
	virtual ~MovementComponent();

	const bool& getCanJump() const;
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;

	const bool getState(const short unsigned state) const;
	void resetJumpCount();
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	void jump();
	void move(const float dir_x, const float& dt);
	void update(const float& dt);
};

#endif
