#include "Grid.hpp"

int Grid::GetGridSizeX() const {
	return sizeX;
}
int Grid::GetGridSizeY() const {
	return sizeY;
}
int Grid::GetLeft() const {
	return left;
}
int Grid::GetTop() const {
	return top;
}
int Grid::GetNumberOfCells() const {
	return sizeX * sizeY;
}
int Grid::GetCellSize() const {
	return cellSize;
}

Cell& Grid::GetSelectedCell(){
	return selectedCell;
}
void Grid::SetSizeX(int x) {
	sizeX = x;
}

void Grid::SetSizeY(int y) {
	sizeY = y;
}

void Grid::SetCellSize(int z) {
	cellSize = z;
}

void Grid::SetTop(int t) {
	top = t;
}
void Grid::SetLeft(int l) {
	left = l;
}
void Grid::Initial(int windowWidth, int windowHeight, int cellDimension) {
	resolutionX = windowWidth;
	resolutionY = windowHeight;
	cellSize = cellDimension;
	sizeX = resolutionX / cellSize;
	sizeY = resolutionY / cellSize;
}
std::vector<sf::Vertex>  Grid::DrawGrid(int left, int top, sf::Color color) {
	SetTop(top);
	SetLeft(left);
	std::vector<sf::Vertex> vertices;
	// draw row
	for (int i = 0; i < sizeY + 1; i += 1) {

		vertices.push_back(sf::Vertex(sf::Vector2f(left, i * cellSize + top), sf::Color::Black));
		vertices.push_back(sf::Vertex(sf::Vector2f(left + resolutionX, i * cellSize + top), color));
	}

	// draw column
	for (int j = 0; j < sizeX + 1; j += 1) {
		vertices.push_back(sf::Vertex(sf::Vector2f(j * cellSize + left, top), sf::Color::Black));
		vertices.push_back(sf::Vertex(sf::Vector2f(j * cellSize + left, resolutionY + top), color));

	}
	SetCellsCoord();

	return  vertices;
}

void Grid::SetCellsCoord() {
	std::vector<Cell> cells;
	for (int i = 0; i < sizeX; i++) {

		for (int j = 0; j < sizeY; j++) {
			Cell cell;
			cell.coordinate = sf::Vector2f(i, j);
			cell.position = sf::Vector2f(floor(i * cellSize + left) , floor(j * cellSize + top));
			cell.center = sf::Vector2f(floor(cell.position.x + cellSize / 2), floor(cell.position.y + cellSize / 2));
			cells.push_back(cell);
		}
		grids.push_back(cells);
		cells.clear();
	}

}

void Grid::FillCell(sf::Color color, Cell& cell) {
	cell.suqare.setFillColor(color);
	cell.suqare.setPosition(cell.center);
	cell.suqare.setSize(sf::Vector2f(cellSize, cellSize));
}


bool Grid::IsWithInCell(Mouse mouse) {

	mouse.SetMouseCoordInGrid(left,top,cellSize);
	if (mouse.GetMouseCoordInWin().x >= left && mouse.GetMouseCoordInWin().x <= resolutionX + left && mouse.GetMouseCoordInWin().y >= top && mouse.GetMouseCoordInWin().y <= resolutionY + top) {
		//std::cout << "Mouse gird coordinate:" << "(" << mouse.GetMouseCoordInGrid().x << "," << mouse.GetMouseCoordInGrid().y << ")" << std::endl;

		//std::cout << "Mouse is within Cell" << std::endl;
		selectedCell = grids[mouse.GetMouseCoordInGrid().x][mouse.GetMouseCoordInGrid().y];
		return true;
	}
	return false;
}


