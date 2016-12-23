#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Wave.h"

#include "Player.h"
#include "Enemy.h"
#include <cstdlib>

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Double Jump");
	window.setFramerateLimit(60);
	sf::Clock clock;

	//Player player;
	//Enemy enemy(sf::Vector2f(float(std::rand() % WINDOW_WIDTH), float(std::rand() % WINDOW_HEIGHT)));
	
	Wave wave;

	// TEMP
	sf::CircleShape center(1.f);
	center.setOrigin(1.f, 1.f);
	center.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
	

	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();

		// Event Handling
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		wave.run(dt, window);

	}

	return EXIT_SUCCESS;
}