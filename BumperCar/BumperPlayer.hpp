#pragma once

#include "PhysicsEntity.hpp"
#include <SFML/Graphics.hpp>

class BumperPlayer : public PhysicsEntity
{
public:
	BumperPlayer();
	~BumperPlayer();

	void incrementScore();
	int getScore();
	void follow(sf::Vector2i mousePosition);
	void setRotationSpeed(float speed);
	void setSpeed(float speed);

private:
	int mScore = 0;
	float mPlayerRotation = 0;
	float mRotationSpeed = 1.5f;
	float mSpeed = 3.0f;
	sf::Vector2f mDirection;
};

