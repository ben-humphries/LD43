#include "GameObject.h"



GameObject::GameObject(std::string dir)
{
	sf::Texture texture;

	if (!texture.loadFromFile(dir)) {
		printf("Error loading texture: Missing texture file");
	}

	Animation * animation = new Animation();
	animation->setSpriteSheet(texture);
	animation->addFrame(sf::IntRect(0, 0, 16, 16));
	animation->addFrame(sf::IntRect(16, 0, 16, 16));
	animation->addFrame(sf::IntRect(32, 0, 16, 16));
	animation->addFrame(sf::IntRect(48, 0, 16, 16));

	AnimatedSprite::setAnimation(*animation);
	AnimatedSprite::play();

	collider = AnimatedSprite::getLocalBounds();
}
GameObject::GameObject() {

}


GameObject::~GameObject()
{
}

void GameObject::update(float dt) {
	AnimatedSprite::update(dt);
}

void GameObject::handleEvent(sf::Event e) { };

sf::Vector2f GameObject::getCenter() {
	sf::Vector2f center;
	center.x = this->getPosition().x + this->getLocalBounds().width / 2;
	center.y = this->getPosition().y + this->getLocalBounds().height / 2;

	return center;
}

//Modified version of collision function from Playground: https://github.com/ben-humphries/Playground
sf::Vector2i GameObject::boundCollision(GameObject * g) {

	sf::Vector2i collision = sf::Vector2i(0, 0); //-1 = left, bottom, 1 = right, top (of g) 

	sf::Vector2f position = this->getPosition();
	sf::Vector2f scale = this->getScale();
	sf::Vector2f origin = this->getOrigin();

	sf::FloatRect col1 = collider;
	col1.left *= scale.x; col1.top *= scale.y;
	col1.left += position.x - origin.x * scale.x; col1.top += position.y - origin.y * scale.y;
	col1.width *= scale.x; col1.height *= scale.y;

	position = g->getPosition();
	scale = g->getScale();
	origin = g->getOrigin();

	sf::FloatRect col2 = g->collider;
	col2.left *= scale.x; col2.top *= scale.y;
	col2.left += position.x - origin.x; col2.top += position.y - origin.y;
	col2.width *= scale.x; col2.height *= scale.y;

	bool left = col1.left <= col2.left && col2.left <= col1.left + col1.width; //collide on the left
	bool right = col2.left <= col1.left && col1.left <= col2.left + col2.width; //collide on the right

	bool top = col1.top <= col2.top && col2.top <= col1.top + col1.height; //collide on the top
	bool bottom = col2.top <= col1.top && col1.top <= col2.top + col2.height; //collide on the bottom


	if ((left || right) && (top || bottom)) {

		float overlapX;
		float overlapY;

		if (left) {
			overlapX = col2.left - (col1.left + col1.width);
			collision.x = -1;
		}
		else {
			overlapX = (col2.left + col2.width) - col1.left;
			collision.x = 1;
		}

		if (top) {
			overlapY = col2.top - (col1.top + col1.height);
			collision.y = 1;
		}
		else {
			overlapY = (col2.top + col2.height) - col1.top;
			collision.y = -1;
		}

		float skinWidth = 0.10;

		if (abs(overlapX) < abs(overlapY)) {

			//This is a hotfix for a collision bug. It is not a good fix. If you're reading this, don't do this.
			if (overlapX > 0) {
				overlapX += skinWidth;
			}
			else {
				overlapX -= skinWidth;
			}

			overlapY = 0;
			collision.y = 0;
		}
		else {


			overlapX = 0;
			collision.x = 0;
		}

		move(sf::Vector2f(overlapX, overlapY));

	}


	return collision;
}
