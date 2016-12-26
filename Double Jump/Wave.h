#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class Wave
{
public:
	Wave();
	void run(const float DT, sf::RenderWindow &window);
	void render(sf::RenderWindow &window);

	void setHasStarted(bool value) { hasStarted = value; }
	bool getHasStarted() { return hasStarted; }
private:
	int createEnemy();
private:
	int waveCount;
	int enemyCount;
	bool hasStarted;
	Player player;
	std::vector<Enemy> enemies;
	std::vector<Bullet> bullets;
	sf::Font font;
	sf::Text waveText;
};

