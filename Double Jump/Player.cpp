#include "Player.h"
#include "Constants.h"

const sf::Vector2f Player::SIZE = sf::Vector2f(30.f, 30.f);
const float Player::SPEED = 700.f;
const float Player::MAX_SPEED = 1000.f;
const float Player::GRAVITY = 35.f;

Player::Player()
{
	velocity = sf::Vector2f(0.f, 0.f);
	setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
}

void Player::update(const float DT)
{
	verticalMovement(DT);


	move(velocity);
	velocity.x = 0.f;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::RectangleShape body(SIZE);
	body.setFillColor(sf::Color::Red);
	body.setOutlineThickness(1.f);
	body.setOutlineColor(sf::Color::White);
	body.setOrigin(SIZE.x / 2.f, SIZE.y / 2.f);
	body.setPosition(getPosition());

	target.draw(body);
}




void Player::verticalMovement(const float DT)
{
	// Move Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (getPosition().x >= SIZE.x / 2.f)
			velocity.x = -SPEED * DT;
	}
	
	// Move Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (getPosition().x <= WINDOW_WIDTH - (SIZE.x / 2.f))
			velocity.x = SPEED * DT;
	}
}