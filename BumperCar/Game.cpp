#include "Game.hpp"
#include <string>
#include <cmath>
#include <iostream>

const float M_PI = 3.141592f;
const float ROTATE_SPEED = 1.5f;
//const float Game::PlayerSpeed = 3500.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
const sf::Vector2f centerOfMap = sf::Vector2f(375.f, 290.f);

Game::Game()
	: mWindow(sf::VideoMode(800, 640), "SFML Application", sf::Style::Close)
	, mTexture()
	, mPlayer()
	, mBall()
	, mFont()
	, mBackground()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
	, mPlayerRotation(0)
	, leftPost()
	, rightPost()
{
	leftPost.setSize(sf::Vector2f(15, 150));
	leftPost.setFillColor(sf::Color(50, 50, 255));
	leftPost.setPosition(sf::Vector2f(30, 245));

	rightPost.setSize(sf::Vector2f(15, 150));
	rightPost.setFillColor(sf::Color(255, 50, 50));
	rightPost.setPosition(sf::Vector2f(755, 245));

	if (!mTexture.loadFromFile("Media/Textures/porsche.png"))
	{
		// Handle loading error
	}

	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setMass(0.002);

	//if (!mBallTexture.loadFromFile("Media/Textures/ball.png"))
	//{
		// Handle loading error
	//}

	//mBall.setTexture(mBallTexture);

	mBall.loadAndSetTexture("Media/Textures/ball.png");

	mBall.setPosition(centerOfMap);

	if (!mBackgroundTexture.loadFromFile("Media/Textures/football-pitch.png"))
	{
		// Handle loading error
	}

	mBackground.setTexture(mBackgroundTexture);

	mFont.loadFromFile("Media/Sansation.ttf");
	
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10); 

	mLeftScoreText.setFont(mFont);
	mLeftScoreText.setPosition(290.f, 5.f);
	mLeftScoreText.setCharacterSize(20);
	mLeftScoreText.setString("Blue: 0");
	mLeftScoreText.setColor(sf::Color(0, 0, 255));

	mRightScoreText.setFont(mFont);
	mRightScoreText.setPosition(450.f, 5.f);
	mRightScoreText.setCharacterSize(20);
	mRightScoreText.setString("Red: 0");
	mRightScoreText.setColor(sf::Color(255, 0, 0));

	mWindow.setFramerateLimit(60);
	mPlayer.setOrigin(mTexture.getSize().x / 2, mTexture.getSize().y / 2);
	
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		//timeSinceLastUpdate += elapsedTime;
		//while (timeSinceLastUpdate > TimePerFrame)
		//{
		//	timeSinceLastUpdate -= TimePerFrame;


		//}
		//processEvents();
		update(elapsedTime);

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	//if (mIsMovingUp)
	//	movement.y -= PlayerSpeed;
	//if (mIsMovingDown)
	//	movement.y += PlayerSpeed;
	//if (mIsMovingLeft)
	//	movement.x -= PlayerSpeed;
	//if (mIsMovingRight)
	//	movement.x += PlayerSpeed;


	if (mPlayer.getGlobalBounds().intersects(mBall.getGlobalBounds())) {
		mBall.applyForce(mBall.getPosition() - mPlayer.getPosition());
		mPlayer.applyForce(mPlayer.getPosition() - mBall.getPosition());

	}
	mBall.update(elapsedTime);
	mPlayer.update(elapsedTime);

	auto left = mPlayer.getRotation() - mPlayerRotation;
	left = left < 0 ? 360 + left : left;
	auto righ = mPlayerRotation - mPlayer.getRotation();
	righ = righ < 0 ? 360 + righ : righ;

	auto pos = mPlayer.getPosition() - static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow));
	mPlayerRotation = (std::atan2f(pos.y, pos.x) * 180.0f / M_PI) + 270.0f;
	if (mPlayerRotation > 360) mPlayerRotation -= 360;
	auto mPlayerRotationRad = (mPlayer.getRotation() - 90) * M_PI / 180.0f;
	mDirection = sf::Vector2f(std::cosf(mPlayerRotationRad), std::sinf(mPlayerRotationRad));

	if (righ < left) {
		mPlayer.rotate(ROTATE_SPEED);
	}
	else {
		mPlayer.rotate(-ROTATE_SPEED);
	}

	mPlayer.move(mDirection * 3.0f);

	auto ballBound = mBall.getGlobalBounds();
	bool hasScored = false;

	if (leftPost.getGlobalBounds().intersects(ballBound)) {
		hasScored = true;
		leftScore++;
		mLeftScoreText.setString("Blue: " + std::to_string(leftScore));
	}
	else if (rightPost.getGlobalBounds().intersects(ballBound)) {
		hasScored = true;
		rightScore++;
		mRightScoreText.setString("Red: " + std::to_string(rightScore));
	}

	if (hasScored) {
		mBall.setPosition(centerOfMap);
		mBall.resetMovement();
	}
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mBackground);
	mWindow.draw(mPlayer);
	mWindow.draw(mBall);
	mWindow.draw(mStatisticsText);
	mWindow.draw(leftPost);
	mWindow.draw(rightPost);
	mWindow.draw(mRightScoreText);
	mWindow.draw(mLeftScoreText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}
