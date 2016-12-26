#include "Bullet.h"
#include "Constants.h"

const float Bullet::LIFETIME = 0.5f;
const float Bullet::SPEED = 2000.f;

Bullet::Bullet(sf::Vector2f startPosition, float angle)
{
	direction = sf::Vector2f(std::cos(angle * DEG2RAD), std::sin(angle * DEG2RAD));
	remainingLife = LIFETIME;
	isAlive = true;

	setPosition(startPosition);
}

void Bullet::update(const float DT)
{
	if (!isAlive) 
		return;

	remainingLife -= DT;
	if (remainingLife <= 0.f) 
		isAlive = false;

	move(direction * SPEED * DT);
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::CircleShape bullet(1.f);
	bullet.setPosition(getPosition());

	target.draw(bullet);
}