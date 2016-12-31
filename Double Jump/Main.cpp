#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Wave.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Double Jump");
	window.setFramerateLimit(FPS);
	sf::Clock clock;
	
	Wave wave;
	
	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();

		// Event Handling
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		wave.run(dt, window);
		wave.render(window);

	}

	return EXIT_SUCCESS;
}