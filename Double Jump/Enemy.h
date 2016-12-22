#pragma once

#include <SFML/Graphics.hpp>

class Enemy : public sf::Drawable, public sf::Transformable
{
	static const sf::Vector2f SIZE;
public:
	Enemy();
	void update(const float DT);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:

};

