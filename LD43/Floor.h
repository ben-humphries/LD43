#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Door.h"
#include "Key.h"

#ifndef FLOOR_H
#define FLOOR_H

class Floor : public sf::Drawable
{
public:
	Floor(std::string backgroundDir, std::string colliderMapDir);
	~Floor();

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Image colliderMap;

	std::vector<GameObject> collidingObjects;

	std::vector<Door*> doors;
	std::vector<Key*> keys;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif
