#include "Wave.h"
#include "Constants.h"
#include <cstdlib>

// DEBUG
#include <iostream>

Wave::Wave()
{
	hasStarted = false;
	waveCount = 1;
	enemyCount = createEnemy(waveCount);

	font.loadFromFile("arial.ttf");
	waveText.setString("Wave: " + std::to_string(waveCount));
	waveText.setFont(font);
	waveText.setCharacterSize(20);
	waveText.setPosition(WINDOW_WIDTH - 100.f, 0.f);
}

void Wave::run(const float DT, sf::RenderWindow &window)
{
	if (hasStarted)
	{
		// DEBUG to advance to next wave.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
			enemyCount = 0;

		// DEBUG
		std::cout << enemyCount << std::endl;

		playerLogic(DT, window);
		bulletLogic(DT);
		enemyLogic(DT);
	}
}

void Wave::render(sf::RenderWindow &window)
{
	waveText.setString("Wave: " + std::to_string(waveCount));
	
	window.clear();
	
	window.draw(player);
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		window.draw(*it);
	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
		window.draw(*it);
	window.draw(waveText);
	
	window.display();
}




int Wave::createEnemy(int wave)
{
	for (int i = 0; i < wave; i++)
		enemies.push_back(Enemy(sf::Vector2f(float(std::rand() % WINDOW_WIDTH), float(std::rand() % (WINDOW_HEIGHT / 3)))));
	
	return enemies.size();
}

void Wave::playerLogic(const float DT, sf::RenderWindow &window)
{
	player.update(DT, window);

	// Player shooting
	if (player.getIsShooting())
	{
		Bullet bullet(sf::Vector2f( player.getPosition().x + (player.getSize().x / 2.f)
									, player.getPosition().y + (player.getSize().y / 2.f))
									, player.getRotation());
		bullets.push_back(bullet);
	}

	// Player is killed (resets everything and sets wave back to 1).
	if (!player.getIsAlive())
	{
		enemies.clear();
		hasStarted = false;
		waveCount = 1;
		enemyCount = createEnemy(waveCount);
		player.reset();
		bullets.clear();
	}
}

void Wave::bulletLogic(const float DT)
{
	// Updating bullets
	std::vector<Bullet>::iterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	{
		if (bulletIt->getIsAlive())
		{
			bulletIt->update(DT);

			// Bullet hits enemy
			std::vector<Enemy>::iterator enemyIt = enemies.begin();
			while (enemyIt != enemies.end())
			{
				if (bulletIt->colliding(*enemyIt))
				{
					enemyIt->setIsAlive(false);
					bulletIt->setIsAlive(false);
				}

				++enemyIt;
			}

			++bulletIt;
		}
		else
			bulletIt = bullets.erase(bulletIt);
	}
}

void Wave::enemyLogic(const float DT)
{
	// Enemy Logic
	std::vector<Enemy>::iterator it = enemies.begin();
	while (it != enemies.end())
	{
		if (it->getIsAlive())
		{
			it->attack(DT, player);
			++it;
		}
		else
		{
			it = enemies.erase(it);
			enemyCount--;
		}
	}

	// All enemies eliminated (resets everything and increments wave).
	if (enemyCount == 0)
	{
		hasStarted = false;
		waveCount++;
		enemyCount = createEnemy(waveCount);
		player.reset();
		bullets.clear();
	}
}