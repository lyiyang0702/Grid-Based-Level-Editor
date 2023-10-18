#ifndef TOOLMENU_HPP
#define TOOLMENU_HPP

#include "Grid.hpp"

class ToolMenu
{
public:
	sf::Sprite brushSprite;
	sf::Sprite eraserSprite;
	sf::Sprite eyedropperSprite;

	void InitToolMenu(sf::RenderWindow &window) {
		sf::RectangleShape menuBg(sf::Vector2f(100,50));
		menuBg.setFillColor(sf::Color::White);
		menuBg.setPosition(window.getPosition().x + (2 / 3) * window.getSize().x, window.getPosition().y + (2 / 3) * window.getSize().y);
		menuDrawables.push_back(menuBg);
		sf::Texture texture;
		texture.loadFromFile("brush.png");
		brushSprite.setTexture(texture);
	}

private:
	std::vector<sf::Drawable> menuDrawables;
};

#endif
