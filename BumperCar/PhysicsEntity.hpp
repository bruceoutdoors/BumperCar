/********************************************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1122702848 Lee Zhen Yong
Contacts    #1 : 0163188854 bruceoutdoors@gmail.com
ID and Name #2 : 1141125087 Hii Yong Lian
Contacts    #2 : 0164111005 yonglian146@gmail.com
********************************************/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <exception>

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
			if (!mTexture.loadFromFile(textureFilePath)) {
				throw new std::runtime_error("Unable to find texture for PhysicsEntity!");
			}

			setTexture(mTexture);
		};
		void update(sf::Time deltaTime) {
			if (forceVector != sf::Vector2f(0, 0)) {
				acceleration = forceVector / mass;
				forceVector = sf::Vector2f(0, 0);
			}
			velocity += deltaTime.asSeconds() * acceleration;
			acceleration = sf::Vector2f(0, 0);

			
			if (getPosition().x > 800 || getPosition().x < 0) {
				if (getPosition().x > 800) {
					setPosition(800, getPosition().y);
				}
				else {
					setPosition(0, getPosition().y);
				}
				velocity.x = -velocity.x;
			}
			if (getPosition().y > 600 || getPosition().y < 0) {
				velocity.y = -velocity.y;
				if (getPosition().y > 600) {
					setPosition(getPosition().x, 600);
				}
				else {
					setPosition(getPosition().x, 0);
				}
				//}
			}
			move(velocity * deltaTime.asSeconds());
			velocity *= friction;
		}

		void resetMovement() {
			forceVector = sf::Vector2f(0, 0);
			velocity = sf::Vector2f(0, 0);
			acceleration = sf::Vector2f(0, 0);
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
		sf::Vector2f getVelocity() {
			return velocity;
		}
		float getMass() {
			return mass;
		}
		void setVelocity(sf::Vector2f input_velocity) {
			velocity = input_velocity;
		}
		void addVelocity(sf::Vector2f input_velocity) {
			velocity += input_velocity;
		}

};