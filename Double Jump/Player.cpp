#include "Player.h"
#include "Constants.h"

#include <iostream>

const sf::Vector2f Player::SIZE = sf::Vector2f(30.f, 30.f);
const float Player::SPEED = 700.f;
const float Player::MAX_SPEED = 1000.f;
const float Player::GRAVITY = 35.f;

Player::Player()
{
	velocity = sf::Vector2f(0.f, 0.f);
	setPosition(WINDOW_WIDTH / 2.f - (SIZE.x / 2.f), WINDOW_HEIGHT / 2.f - (SIZE.y / 2.f));
}

void Player::update(const float DT)
{
	verticalMovement(DT);
	//horizontalMovement(DT);

	//std::cout << getPosition().x << std::endl;

}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::RectangleShape body(SIZE);
	body.setFillColor(sf::Color::Red);
	body.setOutlineThickness(1.f);
	body.setOutlineColor(sf::Color::White);
	body.setPosition(getPosition());

	target.draw(body);
}




void Player::verticalMovement(const float DT)
{
	// Move Left
	if (getPosition().x > 0.f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			velocity.x = -SPEED * DT;
			move(velocity.x, 0.f);
		}
	}
	else
		setPosition(0.f, getPosition().y);
	
	// Move Right
	if (getPosition().x < WINDOW_WIDTH - SIZE.x)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			velocity.x = SPEED * DT;
			move(velocity.x, 0.f);
		}
	}
	else
		setPosition(WINDOW_WIDTH - SIZE.x, getPosition().y);

	velocity.x = 0.f;
}

void Player::horizontalMovement(const float DT)
{
	// TODO

	// Gravity Movement
	if (getPosition().y < WINDOW_HEIGHT - SIZE.y)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)		||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Space)  )
		{
			velocity.y = -SPEED * DT;
		}

		velocity.y += GRAVITY;
		if (velocity.y >= MAX_SPEED)
			velocity.y = MAX_SPEED;
	}
	else
	{
		velocity.y = 0.f;
		setPosition(getPosition().x, WINDOW_HEIGHT - SIZE.y);
		// Died
	}

	move(0.f, velocity.y * DT);
}