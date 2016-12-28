/********************************************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1122702848 Lee Zhen Yong
Contacts    #1 : 0163188854 bruceoutdoors@gmail.com
ID and Name #2 : 1141125087 Hii Yong Lian
Contacts    #2 : 0164111005 yonglian146@gmail.com
********************************************/

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

