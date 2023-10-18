#include "Tilemap.hpp"


void TileMap::SetMapSize(int size) {
    mapSize = size;
}
void TileMap::SliceSourceImg(sf::Texture& texture, int spriteSize) {
    sf::Vector2u sourceSize = texture.getSize();
    SetMapSize(sourceSize.x / spriteSize);
    for (int i = 0; i < sourceSize.x/spriteSize; i++) {
        for (int j = 0; j < sourceSize.y/spriteSize; j++) {
            sf::Sprite sp(texture, sf::IntRect(i * spriteSize, j * spriteSize, spriteSize, spriteSize));
            sp.setOrigin(spriteSize/2, spriteSize/2);
            sp.setPosition(i * spriteSize + spriteSize / 2, j * spriteSize + spriteSize / 2);
           sprites.push_back(sp);
        }; 
    }; 
    mapGrid.Initial(sourceSize.x, sourceSize.y, spriteSize);

}

Tile TileMap::SelectTile() {
    Tile tile;
    Cell& c = mapGrid.GetSelectedCell();
    int cellPos = c.coordinate.x * mapSize + c.coordinate.y;
    tile.sp = sprites[cellPos];
    tile.index = cellPos;
    return tile;
   
}

