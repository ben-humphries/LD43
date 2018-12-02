#pragma once
#include "Command.h"
#include "GameController.h"

#ifndef SCREENFADECOMMAND_H
#define SCREENFADECOMMAND_H

class ScreenFadeCommand :
	public Command
{
public:
	ScreenFadeCommand(float seconds);
	ScreenFadeCommand(float seconds, bool reverse);
	~ScreenFadeCommand();

	float seconds;
	bool reverse = false;
	void run();
};

#endif


ScreenFadeCommand::ScreenFadeCommand(float seconds)
{
	this->seconds = seconds;
}
ScreenFadeCommand::ScreenFadeCommand(float seconds, bool reverse)
{
	this->reverse = reverse;
	this->seconds = seconds;
}

ScreenFadeCommand::~ScreenFadeCommand()
{
}

void ScreenFadeCommand::run() {


	sf::Vector2f size(GameController::window.getSize().x, GameController::window.getSize().y);
	sf::RectangleShape r(size);

	sf::Texture t;
	t.create(GameController::window.getSize().x, GameController::window.getSize().y);
	t.update(GameController::window);
	sf::Sprite start;
	start.setTexture(t);
	
	r.setFillColor(sf::Color(0, 0, 0, 0));

	float alphaPerSecond = 255 / seconds;

	float toAdd = 0;

	sf::View view(sf::FloatRect(0,0,GameController::window.getSize().x, GameController::window.getSize().y));
	view.setCenter(sf::Vector2f(GameController::window.getSize().x / 2, GameController::window.getSize().y / 2));
	GameController::window.setView(view);

	if (reverse) {
		r.setFillColor(sf::Color(0, 0, 0, 255));
	}

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

		toAdd += alphaPerSecond * dt;
		if (toAdd >= 1) {
			sf::Color newColor;
			if (reverse) {
				newColor = sf::Color(0, 0, 0, r.getFillColor().a - 1);
			}
			else {
				newColor = sf::Color(0, 0, 0, r.getFillColor().a + 1);
			}
			r.setFillColor(newColor);
			toAdd = 0;

		}

		GameController::window.clear(sf::Color::White);

		GameController::window.setView(view);

		GameController::window.draw(start);
		GameController::window.draw(r);
		GameController::window.display();

		if (reverse && r.getFillColor().a <= 0) {
			return;
		}
		else if(!reverse && r.getFillColor().a >= 255) {
			return;
		}
	}

}
