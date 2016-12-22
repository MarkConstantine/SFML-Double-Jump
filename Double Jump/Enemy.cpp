#include "Enemy.h"

const sf::Vector2f Enemy::SIZE = sf::Vector2f(15.f, 15.f);

Enemy::Enemy()
{
}

void Enemy::update()
{
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::RectangleShape body(SIZE);
	body.setFillColor(sf::Color::Blue);
	body.setPosition(getPosition());

	target.draw(body);
}