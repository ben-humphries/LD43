#include "InteractingGameObject.h"

#define INTERACTING_DISTANCE 40

InteractingGameObject::InteractingGameObject()
{
}


InteractingGameObject::~InteractingGameObject()
{
}

bool InteractingGameObject::interactWithPlayer() {
	float dx = GameController::player.getCenter().x - this->getCenter().x;
	float dy = GameController::player.getCenter().y - this->getCenter().y;

	float distance = sqrt(dx * dx + dy * dy);

	if (distance < INTERACTING_DISTANCE) {
		return true;
	}
	return false;
}
