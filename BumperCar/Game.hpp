/********************************************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1122702848 Lee Zhen Yong
Contacts    #1 : 0163188854 bruceoutdoors@gmail.com
ID and Name #2 : 1141125087 Hii Yong Lian
Contacts    #2 : 0164111005 yonglian146@gmail.com
********************************************/

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
	sf::Texture	redPorsche;
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


