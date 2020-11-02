#ifndef ANIMATION_H
#define ANIMATION_H


#include "Entity.h"
class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	virtual ~Animation();

	sf::IntRect uvRect;

	void update(int row, float deltaTime);

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};

#endif