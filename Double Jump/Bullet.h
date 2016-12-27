#pragma once

#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Bullet : public sf::Drawable, public sf::Transformable
{
	static const float LIFETIME;
	static const float SPEED;
	static const sf::Vector2f SIZE;
public:
	Bullet(sf::Vector2f startPosition, float angle);
	void update(const float DT);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool colliding(Enemy &enemy) const;

	void setIsAlive(bool value) { isAlive = value; }
	bool getIsAlive() const { return isAlive; }
	sf::Vector2f getRadius() const { return SIZE; }
private:
	sf::Vector2f direction;
	float remainingLife;
	bool isAlive;
};

