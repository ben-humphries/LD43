#pragma once
#include "GameObject.h"
#include "GameController.h"

#ifndef INTERACTINGGAMEOBJECT_H
#define INTERACTINGGAMEOBJECT_H

class InteractingGameObject : public GameObject
{
public:
	InteractingGameObject();
	~InteractingGameObject();

	bool interactWithPlayer();
};

#endif