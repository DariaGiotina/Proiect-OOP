#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;

	this->map.resize(this->maxSize.x, std::vector< std::vector<Tile*> >());
	for (size_t x = 0; x < maxSize.x; x++) 
	{

		for (size_t y = 0; y < maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());
			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers,NULL);
			}
		}
	}
	if (!this->tileSheet.loadFromFile("assets/The Fan-tasy Tileset/Art/Ground Tileset 100x100/4_textures.png")) {
		//load the texture
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE TEXTURE" << "\n";

	}
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < maxSize.x; x++)
	{

		for (size_t y = 0; y < maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}


//Accesors
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}


//Functions
void TileMap::addTile(const unsigned x,const unsigned y,const unsigned z,const sf::IntRect& texture_rect)
{
	//Take three indicies from the mouse pos in the grid and add a tile to that position if the internat tilemap array allows it

	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0) {
		if (this->map[x][y][z] == nullptr) //ok to add tile
		{
			this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileSheet,texture_rect);
			std::cout << "DEBUG: ADDED TILE!" << "\n";
		}

	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0) {
		if (this->map[x][y][z] != nullptr) //ok to remove tile
		{
			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr; 
			std::cout << "DEBUG: REMOVED TILE!" << "\n";
		}

	}
}

//Functions
void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z != nullptr)
					z->render(target);
			}
		}
	}
}