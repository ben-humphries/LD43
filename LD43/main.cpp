#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Floor.h"
#include "GameController.h"
#include "CompositeCommand.h"
#include "WaitCommand.h"
#include "ScreenFadeCommand.h"
#include "ResetWindowCommand.h"
#include "FocusOnGameObjectCommand.h"
#include "DialogCommand.h"

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#define ZOOM 0.5f

Player GameController::player;

Floor * f = new Floor("res/bg.png", "res/collidermap.png");

sf::View GameController::view(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));
sf::RenderWindow GameController::window(sf::VideoMode(800, 600), "LD43");
clock_t GameController::clock;

int main()
{
	clock_t t = clock();

	GameController::player.setPosition(100, 100);
	GameController::view.zoom(ZOOM);


	while (GameController::window.isOpen())
	{
		sf::Event e;
		while (GameController::window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				GameController::window.close();
			else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space) {
				for (int i = 0; i < f->keys.size(); i++) {
					if (f->keys.at(i)->interactWithPlayer()) {
						for (int j = 0; j < f->doors.size(); j++) {
							if (f->keys.at(i)->tag == f->doors.at(j)->tag) {
								CompositeCommand c;
								c.addCommand(ScreenFadeCommand(1.0f, false));
								c.addCommand(WaitCommand(0.1f));
								c.addCommand(FocusOnGameObjectCommand(f->doors.at(j)));
								c.addCommand(ResetWindowCommand(f));
								c.addCommand(ScreenFadeCommand(1.0f, true));
								c.addCommand(WaitCommand(0.5f));
								c.addCommand(ScreenFadeCommand(1.0f, false));
								c.addCommand(WaitCommand(0.1f));
								c.addCommand(FocusOnGameObjectCommand(&GameController::player));
								c.addCommand(ResetWindowCommand(f));
								c.addCommand(ScreenFadeCommand(1.0f, true));

								c.run();
							}
						}
					}
				}
				for (int i = 0; i < f->doors.size(); i++) {
					if (f->doors.at(i)->interactWithPlayer()) {
						printf("opened door\n");
					}
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

		for (int i = 0; i < f->keys.size(); i++) {
			f->keys.at(i)->update(dt);
		}
		for (int i = 0; i < f->doors.size(); i++) {
			f->doors.at(i)->update(dt);
		}

		GameController::window.clear();

		GameController::view.setCenter(GameController::player.getCenter());
		GameController::window.setView(GameController::view);

		GameController::window.draw(*f);

		GameController::window.draw(GameController::player);

		for (int i = 0; i < GameController::player.inventory.size(); i++) {
			GameController::player.inventory.at(i).setPosition(16 * i + GameController::view.getCenter().x - GameController::window.getSize().x/2*ZOOM, 0 + GameController::view.getCenter().y - GameController::window.getSize().y/2*ZOOM);
			GameController::window.draw(GameController::player.inventory.at(i));
		}

		GameController::window.display();
	}

	return 0;
}
