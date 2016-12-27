#include "Enemy.h"

const sf::Vector2f Enemy::SIZE = sf::Vector2f(15.f, 15.f);

Enemy::Enemy(sf::Vector2f startPosition)
{
	setPosition(startPosition);
	isAlive = true;
}

void Enemy::attack(const float DT, Player &player)
{
	if (isAlive)
	{
		sf::Vector2f target((player.getPosition().x + (player.getSize().x / 2.f)) - (getPosition().x + (SIZE.x / 2.f)), 
							(player.getPosition().y + (player.getSize().y / 2.f)) - (getPosition().y + (SIZE.y / 2.f)));
	
		// Enemy has killed player. 
		if (colliding(player))
			player.setIsAlive(false);

		move(target * DT);
	}
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::RectangleShape body(SIZE);
	body.setFillColor(sf::Color::Blue);
	body.setPosition(getPosition());

	target.draw(body);
}

void Enemy::reset(sf::Vector2f position)
{
	setPosition(position);
	isAlive = true;
}




bool Enemy::colliding(Player &player) const
{
	// Checking Vertical Collision
	if (getPosition().y + SIZE.y < player.getPosition().y)
		return false;
	if (getPosition().y > player.getPosition().y + player.getSize().y)
		return false;

	// Checking Horizontal Collision
	if (getPosition().x > player.getPosition().x + player.getSize().x)
		return false;
	if (getPosition().x + SIZE.x < player.getPosition().x)
		return false;

	// Enemy is colliding with player
	return true;
}