#pragma once
#include "GUI.h"

class Tile
{
private:


protected:
	sf::RectangleShape m_tile;

public:
	Tile();
	Tile(float a_gridSize, float a_x, float a_y);
	virtual ~Tile();

	void Update();
	void Render(sf::RenderTarget & a_target);
};

