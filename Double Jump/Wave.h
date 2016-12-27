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
	int createEnemy(int wave);
	void playerLogic(const float DT, sf::RenderWindow &window);
	void bulletLogic(const float DT);
	void enemyLogic(const float DT);
	void reset(int startWave);
private:
	bool hasStarted;
	bool hasDied;
	int waveCount;
	int enemyCount;
	Player player;
	std::vector<Enemy> enemies;
	std::vector<Bullet> bullets;
	sf::Font font;
	sf::Text waveText;
	sf::Text introText;
	sf::Text deathText;
};

