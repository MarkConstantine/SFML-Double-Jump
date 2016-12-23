#include "Wave.h"
#include "Constants.h"
#include <cstdlib>


Wave::Wave()
{
	waveCount = 1;
	enemies.push_back(Enemy(sf::Vector2f(float(std::rand() % WINDOW_WIDTH), float(std::rand() % WINDOW_HEIGHT))));
	enemies.push_back(Enemy(sf::Vector2f(float(std::rand() % WINDOW_WIDTH), float(std::rand() % WINDOW_HEIGHT))));
}

void Wave::run(const float DT, sf::RenderWindow &window)
{
	player.update(DT, window);
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		it->attack(DT, player);
	//enemy.attack(dt, player);
	
	
	window.clear();
	window.draw(player);
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		window.draw(*it);
	//window.draw(enemy);
	window.display();
}