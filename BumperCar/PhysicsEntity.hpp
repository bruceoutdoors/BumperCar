#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class PhysicsEntity : public sf::Sprite {
	sf::Texture mTexture;

	sf::Vector2f forceVector;
	sf::Vector2f velocity;

	float mass = 0.001;
	float friction = 0.99;
	sf::Vector2f acceleration = sf::Vector2f(0,0);

	public:
		PhysicsEntity() {
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

			
			if (getPosition().x > 750 || getPosition().x < 50) {
				if (getPosition().x > 750) {
					setPosition(750, getPosition().y);
				}
				else {
					setPosition(50, getPosition().y);
				}
				std::cout << (velocity.x)
					<< " " <<
					(velocity.y) << std::endl;
				velocity.x = -velocity.x;
			}
			if (getPosition().y > 550 || getPosition().y < 50) {
				std::cout << (velocity.x)
					<< " " <<
					(velocity.y) << std::endl;
				velocity.y = -velocity.y;
				if (getPosition().y > 550) {
					setPosition(getPosition().x, 550);
				}
				else {
					setPosition(getPosition().x, 50);
				}
				//}
			}
			move(velocity * deltaTime.asSeconds());
			velocity *= friction;
		}
		void applyForce(sf::Vector2f fv) {
			//move(fv);
			forceVector += fv;
		}
		void setMass(float input_mass) {
			mass = input_mass;
		}
		void setFriction(float input_friction) {
			friction = input_friction;
		}

};