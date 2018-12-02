#include "GameObject.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameObject
{
public:
	Player();
	~Player();

	std::vector<Animation *> animations;
	std::vector<sf::Texture *> textures;

	Animation * forwardWalkAnimation;
	Animation * backwardWalkAnimation;
	Animation * rightWalkAnimation;
	Animation * leftWalkAnimation;

	void update(float dt);
	void handleEvent(sf::Event e);

	std::vector<GameObject> inventory;
};

#endif

