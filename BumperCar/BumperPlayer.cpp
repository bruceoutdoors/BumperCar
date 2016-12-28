/********************************************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1122702848 Lee Zhen Yong
Contacts    #1 : 0163188854 bruceoutdoors@gmail.com
ID and Name #2 : 1141125087 Hii Yong Lian
Contacts    #2 : 0164111005 yonglian146@gmail.com
********************************************/

#include "BumperPlayer.hpp"

const float M_PI = 3.141592f;

BumperPlayer::BumperPlayer()
{
}


BumperPlayer::~BumperPlayer()
{
}

void BumperPlayer::incrementScore()
{
	mScore++;
}

int BumperPlayer::getScore()
{
	return mScore;
}

void BumperPlayer::follow(sf::Vector2i mousePosition)
{
	auto left = getRotation() - mPlayerRotation;
	left = left < 0 ? 360 + left : left;
	auto righ = mPlayerRotation - getRotation();
	righ = righ < 0 ? 360 + righ : righ;

	auto pos = getPosition() - static_cast<sf::Vector2f>(mousePosition);
	mPlayerRotation = (std::atan2(pos.y, pos.x) * 180.0f / M_PI) + 270.0f;
	if (mPlayerRotation > 360) mPlayerRotation -= 360;
	auto mPlayerRotationRad = (getRotation() - 90) * M_PI / 180.0f;
	mDirection = sf::Vector2f(std::cos(mPlayerRotationRad), std::sin(mPlayerRotationRad));

	if (righ < left) {
		rotate(mRotationSpeed);
	}
	else {
		rotate(-mRotationSpeed);
	}
	addVelocity(mDirection * mSpeed);
	//move(mDirection * mSpeed);
}

void BumperPlayer::setRotationSpeed(float speed)
{
	mRotationSpeed = speed;
}

void BumperPlayer::setSpeed(float speed)
{
	mSpeed = speed;
}
