/********************************************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1122702848 Lee Zhen Yong
Contacts    #1 : 0163188854 bruceoutdoors@gmail.com
ID and Name #2 : 1141125087 Hii Yong Lian
Contacts    #2 : 0164111005 yonglian146@gmail.com
********************************************/

#include "Game.hpp"
#include <string>
#include <cmath>
#include <iostream>

//const float Game::PlayerSpeed = 3500.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
const sf::Vector2f centerOfMap = sf::Vector2f(375.f, 290.f);

Game::Game()
	: mWindow(sf::VideoMode(800, 640), "SFML Application", sf::Style::Close)
	, mTexture()
	, redPorsche()
	, mPlayer()
	, mBall()
	, mFont()
	, mBackground()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, leftPost()
	, rightPost()
{
	leftPost.setSize(sf::Vector2f(15, 150));
	leftPost.setFillColor(sf::Color(50, 50, 255));
	leftPost.setPosition(sf::Vector2f(30, 245));

	rightPost.setSize(sf::Vector2f(15, 150));
	rightPost.setFillColor(sf::Color(255, 50, 50));
	rightPost.setPosition(sf::Vector2f(755, 245));

	if (!mTexture.loadFromFile("Media/Textures/porsche.png")) {
		throw new std::runtime_error("Unable to find texture for blue porsche car!");
	}

	if (!redPorsche.loadFromFile("Media/Textures/porscheRED.png")) {
		throw new std::runtime_error("Unable to find texture for red porsche car!");
	}

	if (!mBackgroundTexture.loadFromFile("Media/Textures/football-pitch.png")) {
		throw new std::runtime_error("Unable to find texture for football field!");
	}

	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setMass(0.005);
	
	mOpponent.setTexture(redPorsche);
	mOpponent.setPosition(500.f, 100.f);
	mOpponent.setMass(0.005);


	mBall.loadAndSetTexture("Media/Textures/ball.png");
	mBall.setPosition(centerOfMap);

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

	
	if (isHost) {
		// bind the listener to a port
		if (listener.listen(53000) != sf::Socket::Done)
		{
			// error...
		}

		// accept a new connection

		if (listener.accept(socket) != sf::Socket::Done)
		{
			// error...
		}
	}
	else {
		sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
		if (status != sf::Socket::Done)
		{
			// error...
		}
	}
	
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
	sf::Packet packet;
	
	if (isHost) {
		mPlayer.follow(sf::Mouse::getPosition(mWindow));
		float x, y, opponentRotation;
		socket.receive(packet);
		packet >> x >> y >> opponentRotation;
		mOpponent.setPosition(sf::Vector2f(x, y));
		mOpponent.setRotation(opponentRotation);
		packet.clear();
		packet << mPlayer.getPosition().x << mPlayer.getPosition().y << mPlayer.getRotation();
		socket.send(packet);
	}
	else {
		mOpponent.follow(sf::Mouse::getPosition(mWindow));
		float x, y, playerRotation;
		packet << mOpponent.getPosition().x << mOpponent.getPosition().y << mOpponent.getRotation();
		socket.send(packet);
		packet.clear();
		socket.receive(packet);
		packet >> x >> y >> playerRotation;
		mPlayer.setPosition(sf::Vector2f(x, y));
		mPlayer.setRotation(playerRotation);

		
	}


	if (mPlayer.getGlobalBounds().intersects(mBall.getGlobalBounds())) {
		mBall.applyForce(mBall.getPosition() - mPlayer.getPosition());
		mPlayer.applyForce(mPlayer.getPosition() - mBall.getPosition());
	}
	if (mOpponent.getGlobalBounds().intersects(mBall.getGlobalBounds())) {
		mBall.applyForce(mBall.getPosition() - mOpponent.getPosition());
		mOpponent.applyForce(mOpponent.getPosition() - mBall.getPosition());
	}
	if (mPlayer.getGlobalBounds().intersects(mOpponent.getGlobalBounds())) {
		mPlayer.applyForce(mPlayer.getPosition() - mOpponent.getPosition());
		mOpponent.applyForce(mOpponent.getPosition() - mPlayer.getPosition());
	}

	mBall.update(elapsedTime);

	mPlayer.update(elapsedTime);
	mOpponent.update(elapsedTime);


	auto ballBound = mBall.getGlobalBounds();
	bool hasScored = false;

	if (leftPost.getGlobalBounds().intersects(ballBound)) {
		hasScored = true;
		mPlayer.incrementScore();
		mLeftScoreText.setString("Blue: " + std::to_string(mPlayer.getScore()));
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
	mWindow.draw(mOpponent);
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
	/*
	if (key == sf::Keyboard::W)
		// blablabla
	else if (key == sf::Keyboard::S)
	*/
}
