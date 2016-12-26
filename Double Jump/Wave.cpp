#include "Wave.h"
#include "Constants.h"
#include <cstdlib>

// DEBUG
#include <iostream>

Wave::Wave()
{
	waveCount = 1;
	enemyCount = createEnemy();
	hasStarted = false;

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

		// Player logic
		player.update(DT, window);

		// Player is killed (resets everything and sets wave back to 1).
		if (!player.getIsAlive())
		{
			waveCount = 1;
			hasStarted = false;
			player.reset();
			enemies.clear();
			enemyCount = createEnemy();
			bullets.clear();
		}

		// Player shooting
		if (player.getIsShooting())
		{
			Bullet bullet(sf::Vector2f( player.getPosition().x + (player.getSize().x / 2.f)
									  , player.getPosition().y + (player.getSize().y / 2.f))
									  , player.getRotation());
			bullets.push_back(bullet);
		}

		// DEBUG
		std::cout << bullets.size() << std::endl;

		// Updating bullets
		std::vector<Bullet>::iterator it = bullets.begin();
		while (it != bullets.end())
		{
			if (it->getIsAlive())
			{
				it->update(DT);
				++it;
			}
			else
				it = bullets.erase(it);
		}
		

		// Enemy Logic
		for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		{
			it->attack(DT, player);
			// TODO - Enemy deaths

			if (!it->getIsAlive())
				enemyCount--;
		}

		// All enemies eliminated (resets everything and increments wave).
		if (enemyCount == 0)
		{
			waveCount++;
			hasStarted = false;
			player.reset();
			for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it)
				it->reset(sf::Vector2f(float(std::rand() % WINDOW_WIDTH), float(std::rand() % (WINDOW_HEIGHT / 3))));
			enemyCount = createEnemy();
			bullets.clear();
		}

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




int Wave::createEnemy()
{
	enemies.push_back(Enemy(sf::Vector2f(float(std::rand() % WINDOW_WIDTH), float(std::rand() % (WINDOW_HEIGHT / 3)))));
	
	return enemies.size();
}