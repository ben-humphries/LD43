#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Player.h"
#include "Floor.h"

#ifndef SFML_STATIC
#define SFML_STATIC
#endif


Player * p = new Player();

Floor * f = new Floor("res/bg.png", "res/collidermap.png");

sf::View view(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));

int main()
{
	clock_t t = clock();

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	p->setPosition(100, 100);
	view.zoom(0.5);


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

		for (int i = 0; i < f->collidingObjects.size(); i++) {
			p->boundCollision(&f->collidingObjects.at(i));
		}

		window.clear();

		sf::Vector2f viewPos = p->getPosition();
		viewPos.x += p->getLocalBounds().width / 2;
		viewPos.y += p->getLocalBounds().height / 2;

		view.setCenter(viewPos);
		window.setView(view);

		window.draw(*f);
		window.draw(*p);
		window.display();
	}

	return 0;
}
