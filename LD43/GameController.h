#include <time.h>
#include <SFML/Graphics.hpp>
#include "Player.h"

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class GameController
{
public:
	static clock_t clock;

	static sf::RenderWindow window;

	static sf::View view;

	static Player player;
};

#endif

