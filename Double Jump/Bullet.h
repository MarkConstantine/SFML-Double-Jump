#pragma once

#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable, public sf::Transformable
{
	static const float LIFETIME;
	static const float SPEED;
public:
	Bullet(sf::Vector2f startPosition, float angle);
	void update(const float DT);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	bool getIsAlive() const { return isAlive; }
private:
	sf::Vector2f direction;
	float remainingLife;
	bool isAlive;
};

