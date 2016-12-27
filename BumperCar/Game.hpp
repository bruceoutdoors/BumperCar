#pragma  once 

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "PhysicsEntity.hpp"
#include "BumperPlayer.hpp"

class Game : private sf::NonCopyable
{
public:
	Game();
	void run();
		 
		 
private: 
	void processEvents();
	void update(sf::Time elapsedTime);
	void render();
		 
	void updateStatistics(sf::Time elapsedTime);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);


private:
	static const float PlayerSpeed;
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;
	sf::Texture	mTexture;
	BumperPlayer mPlayer, mOpponent;

	PhysicsEntity mBall;


	sf::Sprite mBackground;
	sf::Texture	mBackgroundTexture;

	sf::Font mFont;
	sf::Text mStatisticsText;
	sf::Text mLeftScoreText;
	sf::Text mRightScoreText;
	int leftScore = 0;
	int rightScore = 0;

	sf::Time mStatisticsUpdateTime;
	sf::RectangleShape leftPost;
	sf::RectangleShape rightPost;


	sf::TcpSocket socket;
	sf::TcpListener listener;

	bool isHost = false;

	

	std::size_t mStatisticsNumFrames;
};


