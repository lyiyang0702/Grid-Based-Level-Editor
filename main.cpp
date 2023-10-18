#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include "Grid.hpp"
#include "Tilemap.hpp"
#include <algorithm>
#include <fstream>

int main()
{
	enum ToolState { Brush, Eraser, Eyedropper };
	ToolState tool = ToolState::Brush;
	sf::View view;
	sf::Font font;
	TileMap map;
	sf::Texture texture;
	Mouse mouse;
	texture.loadFromFile("tilemap.png");
	map.SliceSourceImg(texture, 32);
	Grid canvasGrid;
	Tile tileOnMouse;
	std::vector<Tile> drawnTiles;
	if (!font.loadFromFile("Roboto-Medium.ttf"))
	{
		std::cout << "loading error" << std::endl;
	}
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Level Editor");
	//view.reset(sf::FloatRect(100, 100, 400, 200));
	window.setFramerateLimit(30);

	bool isClickedOnMap = false;
	bool isClickedOnGrid = false;
	canvasGrid.Initial(1024, 1024, 32);
	std::vector<sf::Vertex> vertices = canvasGrid.DrawGrid(800, 25,sf::Color::Black);
	std::vector<sf::Vertex> mapVertices = map.mapGrid.DrawGrid(0, 0, sf::Color::White);
	bool shouldDrawSpriteOnMouse = true;

	sf::Text text;
	text.setFont(font);
	text.setPosition(25,600);
	text.setString("Press D to Draw, BackSpace to Erase\nPress E for eyedropper (Need to press D to draw) \nPress S to save\nPress L to load ");
	text.setCharacterSize(18);
	while (window.isOpen())
	{
		mouse.SetMouseCoordInWin(window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {

				window.close();
			}


			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (canvasGrid.IsWithInCell(mouse)) {
					isClickedOnGrid = true;
					Cell cell = canvasGrid.GetSelectedCell();
					if (tool == ToolState::Brush) {
							Tile newTile = tileOnMouse;
							newTile.sp.setPosition(cell.center);
							cell.isFilled = true;
							drawnTiles.push_back(newTile);

					}

				}
				if (map.mapGrid.IsWithInCell(mouse)) {
					isClickedOnMap = true;
					isClickedOnGrid = false;
					tileOnMouse = map.SelectTile();

				}
			}

			if (event.type == sf::Event::KeyPressed) {
				isClickedOnMap = false;
				isClickedOnGrid = false;
				if (event.key.code == sf::Keyboard::D) {
					tool = ToolState::Brush;
				}
				else if (event.key.code == sf::Keyboard::BackSpace) {

					tool = ToolState::Eraser;
				}
				else if (event.key.code == sf::Keyboard::E) {
					tool = ToolState::Eyedropper;
				}

				if (event.key.code == sf::Keyboard::S) {
					std::ofstream savefile("Saves.txt");
					if (savefile.is_open())
					{

						for (auto& s : drawnTiles) {
							savefile << std::to_string(s.sp.getPosition().x) <<","<< std::to_string(s.sp.getPosition().y) <<"," << s.index << std::endl;
						}
						savefile.close();
					}
				}
				if (event.key.code == sf::Keyboard::L) {

					std::ifstream savefile("Saves.txt" );
					std::vector<float> tiles;
					if (savefile.is_open())
					{
						std::string line;
						while (std::getline(savefile, line)) {
							std::string delimiter = ",";
							//printf("%s", line.c_str());
							size_t pos = 0;
							std::string token;
							sf::Vector2f tilePos;
							while ((pos = line.find(delimiter)) != std::string::npos) {
								token = line.substr(0, pos);
								line.erase(0, pos + delimiter.length());
								tiles.push_back(std::stof(token));
							}
							tiles.push_back(std::stof(line));
						}
						std::ofstream savefile("Saves.txt");
						savefile.close();
					}

					for (int i = 0; i < tiles.size(); i += 3) {
						Tile newTile;
						//std::cout << tiles[i] << "," << tiles[i + 1] << "," << tiles[i + 2] << std::endl;
						newTile.sp = map.sprites[tiles[i + 2]];
						newTile.sp.setPosition(sf::Vector2f(tiles[i], tiles[i + 1]));
						newTile.index = tiles[i + 2];
						drawnTiles.push_back(newTile);
					}

				}
				//std::cout << "Tool State: " << tool << std::endl;
			}
		}
		window.clear(sf::Color(107,107,107));
		switch (tool)
		{
		case Brush:
			shouldDrawSpriteOnMouse = true;
		    tileOnMouse.sp.setPosition(sf::Vector2f(mouse.GetMouseCoordInWin().x, mouse.GetMouseCoordInWin().y));

			break;
		case Eraser:
			shouldDrawSpriteOnMouse = false;
			if (isClickedOnGrid) {

				if (drawnTiles.size() > 0) {
					for (int i = 0; i < drawnTiles.size(); i++) {
						Cell cell = canvasGrid.GetSelectedCell();
						if (drawnTiles[i].sp.getPosition() == cell.center) {
							cell.isFilled = false;
							drawnTiles.erase(drawnTiles.begin() + i);
							break;
						}
					}
				}
			}
			break;
		case Eyedropper:
			shouldDrawSpriteOnMouse = false;
			//if (isClickedOnGrid) {

				if (drawnTiles.size() > 0) {
					for (int i = 0; i < drawnTiles.size(); i++) {
						Cell cell = canvasGrid.GetSelectedCell();
						if (drawnTiles[i].sp.getPosition() == cell.center) {
							tileOnMouse.sp = drawnTiles[i].sp;
							break;
						}
					}
				}
				tileOnMouse.sp.setPosition(sf::Vector2f(mouse.GetMouseCoordInWin().x, mouse.GetMouseCoordInWin().y));
				shouldDrawSpriteOnMouse = true;
			//}
			break;
		default:
			break;
		}




		//window.setView(view);
		if (shouldDrawSpriteOnMouse) {
			window.draw(tileOnMouse.sp);
		}

		window.draw(&vertices[0], (canvasGrid.GetGridSizeX() + canvasGrid.GetGridSizeY()) * 2 + 4, sf::Lines);
		for (auto& a : map.sprites) {
			window.draw(a);
		}
		for (auto& b : drawnTiles) {
			window.draw(b.sp);
		}

		window.draw(&mapVertices[0], (map.mapGrid.GetGridSizeX() + map.mapGrid.GetGridSizeY()) * 2 + 4, sf::Lines);
		window.draw(text);
		window.display();
	}
	return 0;
}
