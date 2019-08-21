#pragma once
#include "Tile.h"

class WorldMap
{
private:
	sf::Vector2u m_worldSizeCap;
	std::vector<std::vector<std::vector<Tile*>>> m_worldMap; // x, y, z coords
	float m_worldGridSizeF;
	unsigned int m_worldGridSizeU;
	unsigned int m_layers;

public:
	WorldMap(float a_worldGridSize, unsigned int a_width, unsigned int a_height);
	virtual ~WorldMap();

	void AddTile(const unsigned int a_x, const unsigned int a_y, const unsigned int a_z);
	void RemoveTile();

	void Update();
	void Render(sf::RenderTarget & a_target);
};

