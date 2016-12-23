#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class Ball : public sf::Sprite {
	sf::Texture mTexture;

	sf::Vector2f forceVector;
	sf::Vector2f velocity;

	float mass = 0.01;
	float friction = 0.9;
	sf::Vector2f acceleration = sf::Vector2f(0,0);

	public:
		Ball() {
		};

		void loadAndSetTexture(std::string textureFilePath) {
			mTexture.loadFromFile(textureFilePath);
			setTexture(mTexture);
		};
		void update(sf::Time deltaTime) {
			if (forceVector != sf::Vector2f(0, 0)) {
				acceleration = forceVector / mass;
				forceVector = sf::Vector2f(0, 0);
			}
			velocity += deltaTime.asSeconds() * acceleration;
			acceleration = sf::Vector2f(0, 0);
			std::cout << (acceleration.x * deltaTime.asSeconds())
				<< " " <<
				(acceleration.y * deltaTime.asSeconds()) << std::endl;
			move(velocity * deltaTime.asSeconds());
			velocity *= friction;
		}
		void applyForce(sf::Vector2f fv) {
			//move(fv);
			forceVector += fv;
		}

};