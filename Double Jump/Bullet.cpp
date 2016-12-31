#include "Bullet.h"
#include "Constants.h"

const float Bullet::LIFETIME = 0.75f;
const float Bullet::SPEED = 1100.f;
const sf::Vector2f Bullet::SIZE = sf::Vector2f(4.f, 4.f);

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
	sf::RectangleShape bullet(SIZE);
	bullet.setOrigin(SIZE.x / 2.f, SIZE.y / 2.f);
	bullet.setPosition(getPosition());

	target.draw(bullet);
}

bool Bullet::colliding(Enemy &enemy) const
{
	// Checking Vertical Collision
	if (getPosition().y + SIZE.y < enemy.getPosition().y)
		return false;
	if (getPosition().y > enemy.getPosition().y + enemy.getSize().y)
		return false;

	// Checking Horizontal Collision
	if (getPosition().x > enemy.getPosition().x + enemy.getSize().x)
		return false;
	if (getPosition().x + SIZE.x < enemy.getPosition().x)
		return false;

	// Bullet is colliding with enemy
	return true;
}