#include "Wave.h"
#include "Constants.h"
#include <cstdlib>

Wave::Wave()
{
	waveCount = 1;
	enemyCount = createEnemy();
	hasStarted = false;

	font.loadFromFile("arial.ttf");
	waveText.setString("Wave: " + std::to_string(waveCount));
	waveText.setFont(font);
	waveText.setCharacterSize(20);
	waveText.setPosition(WINDOW_WIDTH - 75.f, 0.f);
}

void Wave::run(const float DT, sf::RenderWindow &window)
{
	if (hasStarted)
	{
		// DEBUG
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
			enemyCount = 0;

		player.update(DT, window);

		for (it = enemies.begin(); it != enemies.end(); ++it)
		{
			it->attack(DT, player);
			if (!it->getIsAlive())
				enemyCount--;
		}

		// All enemies eliminated (resets everything and increments wave).
		if (enemyCount == 0)
		{
			waveCount++;
			hasStarted = false;
			player.reset();
			for (it = enemies.begin(); it != enemies.end(); ++it)
				it->reset(sf::Vector2f(float(std::rand() % WINDOW_WIDTH), float(std::rand() % (WINDOW_HEIGHT / 3))));
			enemyCount = createEnemy();
		}

		// Player is killed (resets everything and sets wave back to 1).
		if (!player.getIsAlive())
		{
			waveCount = 1;
			hasStarted = false;
			player.reset();
			enemies.clear();
			enemyCount = createEnemy();
		}
	}
}

void Wave::render(sf::RenderWindow &window)
{
	waveText.setString("Wave: " + std::to_string(waveCount));
	
	window.clear();
	
	window.draw(player);
	for (it = enemies.begin(); it != enemies.end(); ++it)
		window.draw(*it);
	window.draw(waveText);
	
	window.display();
}




int Wave::createEnemy()
{
	enemies.push_back(Enemy(sf::Vector2f(float(std::rand() % WINDOW_WIDTH), float(std::rand() % (WINDOW_HEIGHT / 3)))));
	
	return enemies.size();
}