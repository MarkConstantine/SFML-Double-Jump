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
private:
	bool colliding(Player &player) const;
private:
	bool isAlive;
};

