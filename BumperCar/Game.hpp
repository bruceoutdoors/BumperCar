#pragma  once 

#include <SFML/Graphics.hpp>

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
	sf::Sprite mPlayer;

	sf::Sprite mBall;
	sf::Texture	mBallTexture;


	sf::Sprite mBackground;
	sf::Texture	mBackgroundTexture;

	sf::Font mFont;
	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;

	float mPlayerRotation;
	sf::Vector2f mDirection;

	std::size_t mStatisticsNumFrames;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;
};


