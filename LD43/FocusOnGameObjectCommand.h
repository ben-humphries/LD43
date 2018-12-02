#pragma once
#include "Command.h"
#include "GameObject.h"
#include "GameController.h"

class FocusOnGameObjectCommand :
	public Command
{
public:
	FocusOnGameObjectCommand(GameObject * g);
	~FocusOnGameObjectCommand();

	GameObject * g;

	void run();
};



FocusOnGameObjectCommand::FocusOnGameObjectCommand(GameObject * g)
{
	this->g = g;
}


FocusOnGameObjectCommand::~FocusOnGameObjectCommand()
{
}

void FocusOnGameObjectCommand::run() {
	GameController::view.setCenter(g->getCenter());
}
