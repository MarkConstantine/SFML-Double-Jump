#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Enemy : public sf::Drawable, public sf::Transformable
{
	static const sf::Vector2f SIZE;
public:
	Enemy(sf::Vector2f startPosition);
	void attack(const float DT, Player &player);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void reset(sf::Vector2f position);
	
	void setIsAlive(bool value) { isAlive = value; }
	bool getIsAlive() const { return isAlive; }
	sf::Vector2f getSize() const { return SIZE; }
private:
	bool colliding(Player &player) const;
private:
	bool isAlive;
};