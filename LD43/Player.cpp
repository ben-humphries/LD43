#include "Player.h"

#define PLAYER_SPEED 200.0f
#define ROOT_TWO 1.41421356237

bool movingUp = false, movingDown = false, movingLeft = false, movingRight = false;

Player::Player()
{

	this->setScale(3, 3);

	//Forward walk animation
	forwardWalkAnimation = new Animation();
	//animations.push_back(forwardWalkAnimation);
	sf::Texture * forwardWalkTexture = new sf::Texture();
	//textures.push_back(forwardWalkTexture);

	if (!(*forwardWalkTexture).loadFromFile("res/player-forward.png")) {
		printf("Error loading texture: Missing texture file");
	}

	forwardWalkAnimation->setSpriteSheet(*forwardWalkTexture);

	for (int i = 0; i < 8; i++) {
		forwardWalkAnimation->addFrame(sf::IntRect(i * 32, 0, 32, 32));
	}


	this->setAnimation(*forwardWalkAnimation);
	this->setFrameTime(0.1f);
	this->play();


}


Player::~Player()
{
}

void Player::update(float dt) {
	GameObject::update(dt);

	sf::Vector2f toMove;

	if (movingUp) {
		if (movingDown) {
			toMove.y = 0;
		}
		else if (movingLeft) {
			toMove.y = -PLAYER_SPEED / ROOT_TWO * dt;
			toMove.x = -PLAYER_SPEED / ROOT_TWO * dt;
		}
		else if (movingRight) {
			toMove.y = -PLAYER_SPEED / ROOT_TWO * dt;
			toMove.x = PLAYER_SPEED / ROOT_TWO * dt;
		}
		else {
			toMove.y = -PLAYER_SPEED * dt;
		}
	}
	else if (movingDown) {
		if (movingLeft) {
			toMove.y = PLAYER_SPEED / ROOT_TWO * dt;
			toMove.x = -PLAYER_SPEED / ROOT_TWO * dt;
		}
		else if (movingRight) {
			toMove.y = PLAYER_SPEED / ROOT_TWO * dt;
			toMove.x = PLAYER_SPEED / ROOT_TWO * dt;
		}
		else {
			toMove.y = PLAYER_SPEED * dt;

			this->setAnimation(*forwardWalkAnimation);
			if(!this->isPlaying())
				this->play();
		}
	}
	else if (movingLeft) {
		if (movingRight) {
			toMove.x = 0;
		}
		else {
			toMove.x = -PLAYER_SPEED * dt;
		}
	}
	else if (movingRight) {
		toMove.x = PLAYER_SPEED * dt;
	}
	else {
		toMove.x = 0;
		toMove.y = 0;
	}

	this->move(toMove);

}

void Player::handleEvent(sf::Event e) {
	
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::W) {
			movingUp = true;
		}
		else if (e.key.code == sf::Keyboard::S) {
			movingDown = true;
		}
		else if (e.key.code == sf::Keyboard::A) {
			movingLeft = true;
		}
		else if (e.key.code == sf::Keyboard::D) {
			movingRight = true;
		}
	}
	else if (e.type == sf::Event::KeyReleased) {
		if (e.key.code == sf::Keyboard::W) {
			movingUp = false;
			if (!movingDown && !movingLeft && !movingRight) {
				this->stop();
			}
		}
		else if (e.key.code == sf::Keyboard::S) {
			movingDown = false;
			if (!movingUp && !movingLeft && !movingRight) {
				this->stop();
			}
		}
		else if (e.key.code == sf::Keyboard::A) {
			movingLeft = false;
			if (!movingDown && !movingUp && !movingRight) {
				this->stop();
			}
		}
		else if (e.key.code == sf::Keyboard::D) {
			movingRight = false;
			if (!movingDown && !movingLeft && !movingUp) {
				this->stop();
			}
		}
	}
}
