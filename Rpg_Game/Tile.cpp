#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x,float y,float gridSizef)
{
	this ->shape.setSize(sf::Vector2f(gridSizef, gridSizef));
	this->shape.setFillColor(sf::Color::Magenta);
	this->shape.setPosition(x, y);
}

Tile::~Tile()
{
}

//Functions
void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

