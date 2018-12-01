#include "GameObject.h"


class Player : public GameObject
{
public:
	Player();
	~Player();

	std::vector<Animation *> animations;
	std::vector<sf::Texture *> textures;

	Animation * forwardWalkAnimation;

	void update(float dt);
	void handleEvent(sf::Event e);

};

