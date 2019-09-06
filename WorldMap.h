#pragma once
#include "Tile.h"

class WorldMap
{
private:
	sf::Vector2u m_worldSizeCap;
	std::vector<std::vector<std::vector<Tile*>>> m_worldMap; // x, y, z coords
	sf::Texture m_tileTextures;
	std::string m_textureFile;
	float m_worldGridSizeF;
	unsigned int m_worldGridSizeU;
	unsigned int m_layers;

	void ClearWorldMap();

public:
	WorldMap(float a_worldGridSize, unsigned int a_width, unsigned int a_height, std::string a_file);
	virtual ~WorldMap();

	sf::Texture* GetTileTextures();

	void AddTile(const unsigned int a_x, const unsigned int a_y, const unsigned int a_z, sf::IntRect& a_textureRect);
	void RemoveTile(const unsigned int a_x, const unsigned int a_y, const unsigned int a_z);

	void SaveWorldMap(const std::string a_file);
	bool LoadWorldMap(const std::string a_file);

	void Update();
	void Render(sf::RenderTarget & a_target);
};

