#pragma once
#include "Command.h"
#include "GameController.h"

#ifndef WAITCOMMAND_H
#define WAITCOMMAND_H

class WaitCommand :
	public Command
{
public:
	WaitCommand(float seconds);
	~WaitCommand();

	float seconds;

	void run();

};


WaitCommand::WaitCommand(float seconds)
{
	this->seconds = seconds;
}


WaitCommand::~WaitCommand()
{
}



void WaitCommand::run() {
	float elapsedTime = 0;

	for (;;) {

		sf::Event e;
		while (GameController::window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				GameController::window.close();
			else if (e.type == sf::Event::KeyReleased)
				GameController::player.handleEvent(e);
		}

		float dt = ((float)(clock() - GameController::clock)) / CLOCKS_PER_SEC;
		GameController::clock = clock();
		elapsedTime += dt;

		if (elapsedTime >= seconds) {
			printf("here\n");
			return;
		}
	}
}

#endif