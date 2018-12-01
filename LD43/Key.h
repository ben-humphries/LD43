#pragma once
#include "InteractingGameObject.h"
class Key :
	public InteractingGameObject
{
public:
	Key();
	~Key();

	sf::Texture texture;

	bool interactWithPlayer();
};

