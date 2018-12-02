#pragma once
#include "InteractingGameObject.h"

class Key :
	public InteractingGameObject
{
public:
	Key(std::string tag);
	~Key();

	sf::Texture texture;

	bool pickedUp = false;

	bool interactWithPlayer();
};

