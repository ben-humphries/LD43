#include "Player.h"

#define PLAYER_SPEED 100.0f
#define ROOT_TWO 1.41421356237

bool movingUp = false, movingDown = false, movingLeft = false, movingRight = false;

Animation * currentAnimation;

Player::Player()
{
	//Forward walk animation
	forwardWalkAnimation = new Animation();
	sf::Texture * forwardWalkTexture = new sf::Texture();

	if (!(*forwardWalkTexture).loadFromFile("res/player-forward.png")) {
		printf("Error loading texture: Missing texture file");
	}

	forwardWalkAnimation->setSpriteSheet(*forwardWalkTexture);

	for (int i = 0; i < 8; i++) {
		forwardWalkAnimation->addFrame(sf::IntRect(i * 32, 0, 32, 32));
	}

	//Backward walk animation
	backwardWalkAnimation = new Animation();
	sf::Texture * backwardWalkTexture = new sf::Texture();

	if (!(*backwardWalkTexture).loadFromFile("res/player-backward.png")) {
		printf("Error loading texture: Missing texture file");
	}

	backwardWalkAnimation->setSpriteSheet(*backwardWalkTexture);

	for (int i = 0; i < 8; i++) {
		backwardWalkAnimation->addFrame(sf::IntRect(i * 32, 0, 32, 32));
	}

	//Right walk animation
	rightWalkAnimation = new Animation();
	sf::Texture * rightWalkTexture = new sf::Texture();

	if (!(*rightWalkTexture).loadFromFile("res/player-right.png")) {
		printf("Error loading texture: Missing texture file");
	}

	rightWalkAnimation->setSpriteSheet(*rightWalkTexture);

	for (int i = 0; i < 8; i++) {
		rightWalkAnimation->addFrame(sf::IntRect(i * 32, 0, 32, 32));
	}

	//Left walk animation
	leftWalkAnimation = new Animation();
	sf::Texture * leftWalkTexture = new sf::Texture();

	if (!(*leftWalkTexture).loadFromFile("res/player-left.png")) {
		printf("Error loading texture: Missing texture file");
	}

	leftWalkAnimation->setSpriteSheet(*leftWalkTexture);

	for (int i = 0; i < 8; i++) {
		leftWalkAnimation->addFrame(sf::IntRect(i * 32, 0, 32, 32));
	}


	currentAnimation = forwardWalkAnimation;
	this->setAnimation(*currentAnimation);
	this->setFrameTime(0.1f);
	this->play();

	//this->setScale(3, 3);

	collider = sf::FloatRect(9, 1, 13, 31);
}


Player::~Player()
{
}

void Player::update(float dt) {
	GameObject::update(dt);

	if (!movingUp && !movingDown && !movingRight && !movingLeft) {
		this->stop();
	}

	sf::Vector2f toMove;

	if (movingUp) {
		if (movingDown) {
			toMove.y = 0;
		}
		else if (movingLeft) {
			toMove.y = -PLAYER_SPEED / ROOT_TWO * dt;
			toMove.x = -PLAYER_SPEED / ROOT_TWO * dt;

			currentAnimation = backwardWalkAnimation;
			this->play(*currentAnimation);
		}
		else if (movingRight) {
			toMove.y = -PLAYER_SPEED / ROOT_TWO * dt;
			toMove.x = PLAYER_SPEED / ROOT_TWO * dt;

			currentAnimation = backwardWalkAnimation;
			this->play(*currentAnimation);
		}
		else {
			toMove.y = -PLAYER_SPEED * dt;

			currentAnimation = backwardWalkAnimation;
			this->play(*currentAnimation);
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
		}

		currentAnimation = forwardWalkAnimation;
		this->play(*currentAnimation);
	}
	else if (movingLeft) {
		if (movingRight) {
			toMove.x = 0;
		}
		else {
			toMove.x = -PLAYER_SPEED * dt;

			currentAnimation = leftWalkAnimation;
			this->play(*currentAnimation);
		}
	}
	else if (movingRight) {
		toMove.x = PLAYER_SPEED * dt;

		currentAnimation = rightWalkAnimation;
		this->play(*currentAnimation);
	}
	else {
		toMove.x = 0;
		toMove.y = 0;
	}

	this->move(toMove);
	//can override boundCollision to change animation when hitting a wall.

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
