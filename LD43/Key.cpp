#include "Key.h"



Key::Key()
{

	if (!texture.loadFromFile("res/key.png")) {
		printf("Error loading texture: Missing texture file");
	}

	Animation * animation = new Animation();
	animation->setSpriteSheet(texture);
	animation->addFrame(sf::IntRect(0, 0, 16, 16));
	animation->addFrame(sf::IntRect(16, 0, 16, 16));
	animation->addFrame(sf::IntRect(32, 0, 16, 16));
	animation->addFrame(sf::IntRect(48, 0, 16, 16));
	animation->addFrame(sf::IntRect(64, 0, 16, 16));


	AnimatedSprite::setAnimation(*animation);
	AnimatedSprite::setFrameTime(0.11f);
	AnimatedSprite::play();

	collider = AnimatedSprite::getLocalBounds();
}


Key::~Key()
{
}

bool Key::interactWithPlayer() {

	return InteractingGameObject::interactWithPlayer();
}
