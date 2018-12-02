#pragma once
#include "Command.h"
#include "GameController.h"
#include "Floor.h"

#define ZOOM 0.5

class ResetWindowCommand :
	public Command
{
public:
	ResetWindowCommand(Floor * f);
	~ResetWindowCommand();

	Floor * fl;

	void run();
};



ResetWindowCommand::ResetWindowCommand(Floor * f)
{
	this->fl = f;
}


ResetWindowCommand::~ResetWindowCommand()
{
}

void ResetWindowCommand::run() {
	GameController::window.clear();

	//GameController::view.setCenter(GameController::player.getCenter());
	GameController::window.setView(GameController::view);

	GameController::window.draw(*fl);

	GameController::window.draw(GameController::player);

	for (int i = 0; i < GameController::player.inventory.size(); i++) {
		GameController::player.inventory.at(i).setPosition(16 * i + GameController::view.getCenter().x - GameController::window.getSize().x / 2 * ZOOM, 0 + GameController::view.getCenter().y - GameController::window.getSize().y / 2 * ZOOM);
		GameController::window.draw(GameController::player.inventory.at(i));
	}
}
