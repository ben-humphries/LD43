#pragma once
#include "GameObject.h"
#include "GameController.h"
class InteractingGameObject : public GameObject
{
public:
	InteractingGameObject();
	~InteractingGameObject();

	bool interactWithPlayer();
};

