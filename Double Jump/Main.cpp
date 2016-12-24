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
	
	Wave wave;
	
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			wave.setHasStarted(true);

		if (wave.getHasStarted())
			wave.run(dt, window);

		wave.render(window);
	}

	return EXIT_SUCCESS;
}