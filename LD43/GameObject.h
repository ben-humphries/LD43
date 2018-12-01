#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include "AnimatedSprite.h"
#include "Animation.h"
#include <vector>

class GameObject : public AnimatedSprite
{
public:
	GameObject();
	GameObject(std::string dir);
	~GameObject();

	sf::FloatRect collider;

	virtual void update(float dt);
	virtual sf::Vector2i boundCollision(GameObject * g);

	virtual void handleEvent(sf::Event e);

	sf::Vector2f getCenter();
};

