#ifndef TILE_H
#define TILE_H


class Tile
{
private:

protected:
	sf::RectangleShape shape;
public:
	Tile();
	Tile(float x, float y, float gridSizef);
	virtual ~Tile();

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

#endif // !TILE_H