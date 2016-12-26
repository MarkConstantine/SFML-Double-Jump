#include "Player.h"
#include "Constants.h"
#include <cmath>

const sf::Vector2f Player::SIZE = sf::Vector2f(30.f, 30.f);
const float Player::SPEED = 700.f;
const float Player::MAX_SPEED = 1000.f;
const float Player::GRAVITY = 35.f;

Player::Player()
{
	velocity = sf::Vector2f(0.f, 0.f);
	setPosition(WINDOW_WIDTH / 2.f - (SIZE.x / 2.f), WINDOW_HEIGHT / 2.f - (SIZE.y / 2.f));
	isAlive = true;
	wasUpPressed = false;
	isShooting = false;
	wasLMBPressed = false;
}

void Player::update(const float DT, const sf::RenderWindow &WINDOW)
{
	if (isAlive)
	{
		horizontalMovement(DT);
		verticalMovement(DT);
		gunMovement(DT, WINDOW);
	}
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::RectangleShape body(SIZE);
	body.setFillColor(sf::Color::Red);
	body.setOutlineThickness(1.f);
	body.setOutlineColor(sf::Color::White);
	body.setPosition(getPosition());
	
	sf::RectangleShape gun(sf::Vector2f(SIZE.x * 1.2f, 1.f));
	gun.setPosition(getPosition().x + SIZE.x / 2.f, getPosition().y + SIZE.y / 2.f);
	gun.setRotation(getRotation());

	target.draw(body);
	target.draw(gun);
}

void Player::reset()
{
	velocity = sf::Vector2f(0.f, 0.f);
	setPosition(WINDOW_WIDTH / 2.f - (SIZE.x / 2.f), WINDOW_HEIGHT / 2.f - (SIZE.y / 2.f));
	setRotation(90.f);
	isAlive = true;
	wasUpPressed = false;
	isShooting = false;
	wasLMBPressed = false;
}




void Player::horizontalMovement(const float DT)
{
	// Move left
	if (getPosition().x > 0.f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			velocity.x = -SPEED;
			move(velocity.x * DT, 0.f);
		}
	}
	else
		setPosition(0.f, getPosition().y);
	
	// Move right
	if (getPosition().x < WINDOW_WIDTH - SIZE.x)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			velocity.x = SPEED;
			move(velocity.x * DT, 0.f);
		}
	}
	else
		setPosition(WINDOW_WIDTH - SIZE.x, getPosition().y);

	velocity.x = 0.f;
}

void Player::verticalMovement(const float DT)
{
	bool isUpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::W)
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	// Gravity movement
	if (getPosition().y < WINDOW_HEIGHT - SIZE.y)
	{
		// Jumping
		if (isUpPressed && !wasUpPressed && getPosition().y > 0.f)
			velocity.y = -SPEED;

		// Gravity
		velocity.y += GRAVITY;
		
		// Limits vertical speed
		if (velocity.y >= MAX_SPEED)
			velocity.y = MAX_SPEED;
	}
	// Died
	else 
	{
		velocity.y = 0.f;
		setPosition(getPosition().x, WINDOW_HEIGHT - SIZE.y);
		isAlive = false;
	}

	wasUpPressed = isUpPressed;
	move(0.f, velocity.y * DT);
}

void Player::gunMovement(const float DT, const sf::RenderWindow &WINDOW)
{
	bool isLMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	sf::Vector2f gunDirection(sf::Mouse::getPosition(WINDOW).x - (getPosition().x + SIZE.x / 2.f),
							  sf::Mouse::getPosition(WINDOW).y - (getPosition().y + SIZE.y / 2.f));
	setRotation(atan2f(gunDirection.y, gunDirection.x) * RAD2DEG);

	// Shooting
	if (isLMBPressed && !wasLMBPressed)
		isShooting = true;
	else
		isShooting = false;

	wasLMBPressed = isLMBPressed;
}