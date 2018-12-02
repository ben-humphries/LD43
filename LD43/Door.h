#pragma once
#include "InteractingGameObject.h"

#ifndef DOOR_H
#define DOOR_H

class Door :
	public InteractingGameObject
{
public:
	Door(std::string tag);
	~Door();

	sf::Texture texture;

	bool interactWithPlayer();

	void open();
	void update(float dt);

	bool isOpen = false;

	Animation * openAnimation;
	Animation * currentAnimation;

};

#endif

