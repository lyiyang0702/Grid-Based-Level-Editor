#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include <SFML/Graphics.hpp>
#include "Grid.hpp"

struct Tile {
	sf::Sprite sp;
	int index;
};
class TileMap {
	
public:
	std::vector<sf::Sprite> sprites;
	Grid mapGrid;
	void SliceSourceImg(sf::Texture &texture, int spriteSize);
	Tile SelectTile();
	void SetMapSize(int size);
private:
	int mapSize;
};


#endif // !TILEMAP_HPP

