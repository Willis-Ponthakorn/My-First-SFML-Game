#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include<iostream>
#include<string>
#include<map>

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class AnimationComponent
{
private:
	class Animation
	{
	public:
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet,
			float animation_timer,
			int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
			: sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), width(width), height(height)
		{
			this->timer = 0.f;
			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

		void play(const float& dt)
		{
			this->timer += 25.f * dt;
			if (this->timer >= this->animationTimer)
			{
				this->timer = 0.f;

				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else
				{
					this->currentRect.left = this->startRect.left;
				}

				this->sprite.setTextureRect(this->currentRect);
			}
		}

		void play(const float& dt, const float& modifier, const float& modifier_max)
		{

			this->timer += (modifier  / modifier_max) * 100.f * dt;
			if (this->timer >= this->animationTimer)
			{
				this->timer = 0.f;

				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else
				{
					this->currentRect.left = this->startRect.left;
				}

				this->sprite.setTextureRect(this->currentRect);
			}
		}

		void reset() 
		{
			this->timer = 0.f;
			this->currentRect = this->startRect;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	void addAnimation(const std::string key,
		float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	void play(const std::string key, const float& dt);
	void play(const std::string key, const float& dt, const float& modifier, const float& modifier_max);
};
#endif

