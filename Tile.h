#pragma once
#include "GUI.h"

class Tile
{
private:
	enum TILE_TYPES { GRASS = 0 };

protected:
	sf::RectangleShape m_tile;
	short int m_tileType;		// breakable, lava, water, etc
	bool m_tileCollision;

public:
	Tile();
	Tile(unsigned int a_x, unsigned int a_y, float a_gridSize, 
		sf::Texture& a_texture, sf::IntRect a_textureRect, 
		short a_tileType, bool a_tileCollision);
	virtual ~Tile();

	const std::string GetAsString() const;

	void Update();
	void Render(sf::RenderTarget & a_target);
};

