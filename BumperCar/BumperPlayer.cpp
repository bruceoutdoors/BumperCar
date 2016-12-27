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
	mPlayerRotation = (std::atan2f(pos.y, pos.x) * 180.0f / M_PI) + 270.0f;
	if (mPlayerRotation > 360) mPlayerRotation -= 360;
	auto mPlayerRotationRad = (getRotation() - 90) * M_PI / 180.0f;
	mDirection = sf::Vector2f(std::cosf(mPlayerRotationRad), std::sinf(mPlayerRotationRad));

	if (righ < left) {
		rotate(mRotationSpeed);
	}
	else {
		rotate(-mRotationSpeed);
	}

	move(mDirection * mSpeed);
}

void BumperPlayer::setRotationSpeed(float speed)
{
	mRotationSpeed = speed;
}

void BumperPlayer::setSpeed(float speed)
{
	mSpeed = speed;
}
