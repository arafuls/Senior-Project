#include "stdafx.h"
#include "WorldMap.h"


WorldMap::WorldMap(float a_worldGridSize, unsigned int a_width, unsigned int a_height)
{
	// Set max size of the world
	m_worldSizeCap.x = a_width;
	m_worldSizeCap.y = a_height;
	m_layers = 1;

	// Set size of the world grid
	m_worldGridSizeF = a_worldGridSize;
	m_worldGridSizeU = static_cast<unsigned int>(m_worldGridSizeF);

	// Initialize the world map by pushing in empty tiles into 3D vector
	m_worldMap.resize(m_worldSizeCap.x);
	for (size_t x = 0; x < m_worldSizeCap.x; x++)
	{
		m_worldMap.push_back(std::vector <std::vector <Tile*> >());

		for (size_t y = 0; y < m_worldSizeCap.y; y++)
		{
			m_worldMap[x].resize(m_worldSizeCap.y);
			m_worldMap[x].push_back(std::vector <Tile*>());

			for (size_t z = 0; z < m_layers; z++)
			{
				m_worldMap[x][y].resize(m_layers);
				m_worldMap[x][y].push_back(NULL);
				/*
				m_worldMap[x][y].push_back(
					new Tile
					(
						x * m_worldGridSizeF,
						y * m_worldGridSizeF,
						m_worldGridSizeF
					)
				);
				*/
			}
		}
	}


}



WorldMap::~WorldMap()
{
	// Delete the entire world map
	for (size_t x = 0; x < m_worldSizeCap.x; x++)
	{
		for (size_t y = 0; y < m_worldSizeCap.y; y++)
		{
			for (size_t z = 0; z < m_layers; z++)
			{
				delete m_worldMap[x][y][z];
			}
		}
	}
}


/*
NAME
	void WorldMap::AddTile()

SYNOPSIS
	const float a_x	- X coordinate
	const float a_y	- Y coordinate

DESCRIPTION
	This function will allow the user to place a tile onto the world map in 
	editor mode. The tile will be placed at the mouse coordinates _IF_ the 
	coordinates are within the world map vector.

AUTHOR
	Austin Rafuls

DATE
	9:56pm 8/9/2019
*/
void WorldMap::AddTile(const unsigned int a_x, const unsigned int a_y, const unsigned int a_z)
{
	// If the desired tile location is within the world map
	if ((a_x >= 0 && a_x < m_worldSizeCap.x) &&
		(a_y >= 0 && a_y < m_worldSizeCap.y) &&
		(a_z >= 0 && a_z < m_layers))
	{
		// If the desired tile is not already claimed
		if (m_worldMap[a_x][a_y][a_z] == NULL)
		{
			// Add the tile
			m_worldMap[a_x][a_y][a_z] = 
				new Tile(
					a_x * m_worldGridSizeF,	// x
					a_y * m_worldGridSizeF,	// y
					m_worldGridSizeF		// z
				);
		}
	}
}



void WorldMap::RemoveTile()
{
}


/*
NAME
	void WorldMap::Update()

DESCRIPTION
	This function will constantly update the game's world map so the player
	knows where they are currently relative to the world map.

AUTHOR
	Austin Rafuls

DATE
	12:42pm 8/9/2019
*/
void WorldMap::Update()
{
}


/*
NAME
	void WorldMap::Render()

SYNOPSIS
	sf::RenderTarget* a_target	- The current window to draw to.

DESCRIPTION
	This function will draw onto the window, a_target, the current world map
	for entities to traverse.

AUTHOR
	Austin Rafuls

DATE
	9:44pm 8/9/2019
*/
void WorldMap::Render(sf::RenderTarget & a_target)
{
	for (std::vector<std::vector<Tile*>> & x_tiles : m_worldMap)
	{
		for (std::vector<Tile*> & y_tiles : x_tiles)
		{
			for (Tile * z_tiles : y_tiles)
			{
				if (z_tiles != NULL)
				{
					z_tiles->Render(a_target);
				}
			}
		}
	}
}
