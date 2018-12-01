#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Floor : public sf::Drawable
{
public:
	Floor(std::string backgroundDir, std::string colliderMapDir);
	~Floor();

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Image colliderMap;

	std::vector<GameObject> collidingObjects;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

