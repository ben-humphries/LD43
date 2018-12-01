#include "Floor.h"

#define SHOW_COLLIDERS false

#define COLLIDER_START sf::Color(0,0,255,255)
#define COLLIDER sf::Color(255,0,0,255)

Floor::Floor(std::string backgroundDir, std::string colliderMapDir)
{
	if (!backgroundTexture.loadFromFile(backgroundDir)) {
		printf("Error loading texture: Missing texture file");
	}

	backgroundSprite.setTexture(backgroundTexture);

	if (!colliderMap.loadFromFile(colliderMapDir)) {
		printf("Error loading texture: Missing texture file");
	}

	int w = colliderMap.getSize().x;
	int h = colliderMap.getSize().y;

	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {

			sf::Color currentPixel = colliderMap.getPixel(x, y);

			if (currentPixel == COLLIDER_START) {
				sf::FloatRect collider;
				collider.left = 0;
				collider.top = 0;

				int i = x+1; int j = y;

				while (i < w - 1 && colliderMap.getPixel(i, j) == COLLIDER) { i++; }
				while (j < h - 1 && colliderMap.getPixel(i-1, j) == COLLIDER) { j++; }
				

				collider.width = i - x;
				collider.height = j - y;

				GameObject * g = new GameObject();
				g->collider = collider;
				g->setPosition(x, y);
				collidingObjects.push_back(*g);
			}
		}
	}
}


Floor::~Floor()
{
}

void Floor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundSprite, states);

	if (SHOW_COLLIDERS) {
		for (int i = 0; i < collidingObjects.size(); i++) {

			sf::RectangleShape s;
			s.setPosition(collidingObjects.at(i).getPosition());
			s.setSize(sf::Vector2f(collidingObjects.at(i).collider.width, collidingObjects.at(i).collider.height));

			s.setFillColor(sf::Color(0, 255, 0, 255));
			target.draw(s, states);
		}
	}

}