#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Grid.hpp"
class Mouse
{

	sf::Mouse mouse;
public:

	void SetMouseCoordInWin(sf::RenderWindow& window) {
		mouseCoordInWin = sf::Vector2i(mouse.getPosition(window).x, mouse.getPosition(window).y);
	}
	sf::Vector2i GetMouseCoordInWin() const {
		return mouseCoordInWin;
	}
	void SetMouseCoordInGrid(int left, int top, int cellSize) {
		mouseCoordInGrid = sf::Vector2i((mouseCoordInWin.x - left) /cellSize, (mouseCoordInWin.y - top) /cellSize);

	}

	sf::Vector2i GetMouseCoordInGrid() const {
		return mouseCoordInGrid;
	}
private:
	sf::Vector2i mouseCoordInWin;
	sf::Vector2i mouseCoordInGrid;
};


#endif
