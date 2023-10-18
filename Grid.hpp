#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <utility>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Mouse.hpp"
struct Cell {
	bool isFilled;
	sf::RectangleShape suqare;
	sf::Vector2f position;
	sf::Vector2f coordinate;
	sf::Vector2f center;
};
class Grid {

public:
	int GetGridSizeX() const;
	int GetGridSizeY() const;
	int GetTop() const;
	int GetLeft() const;
	int GetNumberOfCells() const;
	int GetCellSize() const;
	Cell& GetSelectedCell();
	void SetTop(int t);
	void SetLeft(int l);
	void SetSizeX(int x);
	void SetSizeY(int y);
	void SetCellSize(int z);
	void Initial(int windowWidth, int windowHeight, int cellDimension);
	std::vector<sf::Vertex> DrawGrid(int left, int top, sf::Color color);
	void SetCellsCoord();
	void FillCell(sf::Color color, Cell& cell);
	std::vector <std::vector<Cell>> grids;
	bool IsWithInCell(Mouse mouse);

private:
	int sizeX = 0 ;
	int sizeY = 0;
	int resolutionX = 0;
	int resolutionY = 0;
	int cellSize = 0;
	int top = 0;
	int left = 0;
	Cell selectedCell;
};
#endif // !GRID_HPP
