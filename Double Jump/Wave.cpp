#include "Wave.h"
#include "Constants.h"
#include <cstdlib>

Wave::Wave()
{
	hasStarted = false;
	hasDied = false;
	waveCount = 1;
	enemyCount = createEnemy(waveCount);

	font.loadFromFile("arial.ttf");
	
	waveText.setFont(font);
	waveText.setString("Wave: " + std::to_string(waveCount));
	waveText.setCharacterSize(20);
	waveText.setPosition(WINDOW_WIDTH - 100.f, 0.f);

	introText.setFont(font);
	introText.setString("Press shift to start the wave.\n    Don't touch the ground!");
	introText.setCharacterSize(25);
	introText.setPosition((WINDOW_WIDTH / 2.f) - (introText.getGlobalBounds().width / 2.f), WINDOW_HEIGHT / 3.f);

	deathText.setFont(font);
	deathText.setString("             You Died!\n  You made it to wave " + std::to_string(waveCount) + ".\nPress shift to play again!");
	deathText.setCharacterSize(25);
	deathText.setPosition((WINDOW_WIDTH / 2.f) - (introText.getGlobalBounds().width / 2.f) + 25.f, WINDOW_HEIGHT / 3.f);
}

void Wave::run(const float DT, sf::RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		hasStarted = true;

	if (hasStarted)
	{
		playerLogic(DT, window);
		bulletLogic(DT);
		enemyLogic(DT);
	}
}

void Wave::render(sf::RenderWindow &window)
{
	waveText.setString("Wave: " + std::to_string(waveCount));
	deathText.setString("             You Died!\n  You made it to wave " + std::to_string(waveCount) + ".\nPress shift to play again!");
	
	window.clear();
	
	window.draw(player);
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		window.draw(*it);
	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
		window.draw(*it);
	if (!hasStarted)
		window.draw(introText);
	if (hasDied)
		window.draw(deathText);
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
		Bullet bullet(sf::Vector2f( player.getPosition().x + (player.getSize().x / 2.f),
									player.getPosition().y + (player.getSize().y / 2.f)),
									player.getRotation());
		bullets.push_back(bullet);
	}

	// Player is killed (resets everything and sets wave back to 1).
	if (!player.getIsAlive())
	{
		hasDied = true;
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			reset(1);
	}
}

void Wave::bulletLogic(const float DT)
{
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
	std::vector<Enemy>::iterator it = enemies.begin();
	while (it != enemies.end())
	{
		if (it->getIsAlive())
		{
			it->attack(DT, player, enemies);
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
		reset(++waveCount);
	}
}

void Wave::reset(int startWave)
{
	hasStarted = false;
	hasDied = false;
	if (startWave == 1)
	{
		waveCount = 1;
		enemies.clear();
	}
	enemyCount = createEnemy(waveCount);
	player.reset();
	bullets.clear();
}