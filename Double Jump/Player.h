#pragma once

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable, public sf::Transformable
{
	static const sf::Vector2f SIZE;
	static const float SPEED;
	static const float MAX_SPEED;
	static const float GRAVITY;
public:
	Player();
	void update(const float DT);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
	void verticalMovement(const float DT);
private:
	sf::Vector2f velocity;
};