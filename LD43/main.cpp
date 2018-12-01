#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Player.h"

#ifndef SFML_STATIC
#define SFML_STATIC
#endif


Player * p = new Player();

int main()
{
	clock_t t = clock();

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");


	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
			else
				p->handleEvent(e);
		}

		float dt = ((float)(clock() - t)) / CLOCKS_PER_SEC;
		t = clock();

		p->update(dt);
		window.clear();
		window.draw(*p);
		window.display();
	}

	return 0;
}
