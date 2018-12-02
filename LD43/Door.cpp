#include "Door.h"


Door::Door(std::string tag)
{
	this->tag = tag;

	if (!texture.loadFromFile("res/door-open.png")) {
		printf("Error loading texture: Missing texture file");
	}

	Animation * animation = new Animation();
	animation->setSpriteSheet(texture);
	
	for (int i = 0; i < 7; i++) {
		animation->addFrame(sf::IntRect(i * 32, 0, 32, 32));
	}

	openAnimation = new Animation();
	animation->setSpriteSheet(texture);
	animation->addFrame(sf::IntRect(6 * 32, 0, 32, 32));

	currentAnimation = animation;
	AnimatedSprite::setAnimation(*currentAnimation);
	AnimatedSprite::setFrameTime(0.11f);
	AnimatedSprite::setLooped(false);
	collider = sf::FloatRect(10, 0, 11, 32);
	this->stop();
}


Door::~Door()
{
}

bool Door::interactWithPlayer() {
	if (InteractingGameObject::interactWithPlayer()) {
		for (int i = 0; i < GameController::player.inventory.size(); i++) {
			if (GameController::player.inventory.at(i).tag == this->tag) {
				GameController::player.inventory.erase(GameController::player.inventory.begin() + i);
				open();
				return true;
			}
		}
	}
	return false;
}

void Door::open() {
	this->play();
	isOpen = true;
}

void Door::update(float dt) {

	if (!isOpen) {
		GameController::player.boundCollision(this);
	}
	else {
		if (!this->isPlaying()) {
			this->setFrame(6);
			this->pause();
		}
	}

	InteractingGameObject::update(dt);

}
