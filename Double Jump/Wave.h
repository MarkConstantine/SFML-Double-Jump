#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Enemy.h"

class Wave
{
public:
	Wave();
	void run(const float DT, sf::RenderWindow &window);
private:
	int waveCount;
	Player player;
	std::vector<Enemy> enemies;
};

