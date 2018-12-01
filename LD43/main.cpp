#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Floor.h"
#include "CompositeCommand.h"
#include "WaitCommand.h"
#include "ScreenFadeCommand.h"
#include "GameController.h"
#include "Key.h"

#ifndef SFML_STATIC
#define SFML_STATIC
#endif


Player GameController::player;

Floor * f = new Floor("res/bg.png", "res/collidermap.png");
Key * key = new Key();

sf::View GameController::view(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));

sf::RenderWindow GameController::window(sf::VideoMode(800, 600), "SFML works!");
clock_t GameController::clock;

int main()
{
	clock_t t = clock();

	key->setPosition(200, 200);

	GameController::player.setPosition(100, 100);
	GameController::view.zoom(0.5f);


	while (GameController::window.isOpen())
	{
		sf::Event e;
		while (GameController::window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				GameController::window.close();
			else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space) {
				if (key->interactWithPlayer()) {
					printf("picked up key\n");
				}
			}
			else
				GameController::player.handleEvent(e);
		}

		float dt = ((float)(clock() - GameController::clock)) / CLOCKS_PER_SEC;
		GameController::clock = clock();

		GameController::player.update(dt);

		for (int i = 0; i < f->collidingObjects.size(); i++) {
			GameController::player.boundCollision(&f->collidingObjects.at(i));
		}

		key->update(dt);

		GameController::window.clear();

		GameController::view.setCenter(GameController::player.getCenter());
		GameController::window.setView(GameController::view);

		GameController::window.draw(*f);
		GameController::window.draw(*key);
		GameController::window.draw(GameController::player);
		GameController::window.display();
	}

	return 0;
}
