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
	void update(const float DT, const sf::RenderWindow &WINDOW);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void setIsAlive(bool value) { isAlive = value; }
	bool getIsAlive() const { return isAlive; }
private:
	void horizontalMovement(const float DT);
	void verticalMovement(const float DT);
	void gunMovement(const float DT, const sf::RenderWindow &WINDOW);
private:
	sf::Vector2f velocity;
	bool isAlive;
	bool wasUpPressed;
};