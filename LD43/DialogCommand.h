#pragma once
#include "Command.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameController.h"

#ifndef DIALOGCOMMAND_H
#define DIALOGCOMMANG_H

class DialogCommand :
	public Command
{
public:
	DialogCommand(std::vector<std::string> * lines);
	~DialogCommand();

	std::vector<std::string> * lines;

	void run();
};

#endif



DialogCommand::DialogCommand(std::vector<std::string> * lines)
{
	this->lines = lines;
}


DialogCommand::~DialogCommand()
{
}

inline void DialogCommand::run()
{
	int currentLine = 0;


	for (int i = 0; i < lines->size(); i++) {
		std::cout << lines->at(i) << std::endl;

		bool a = true;
		while(a) {
			sf::Event e;
			while (GameController::window.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
					GameController::window.close();
				else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space) {
					a = false;
					break;
				}
			}

		}
	}
}

