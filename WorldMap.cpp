#include "stdafx.h"
#include "WorldMap.h"

/*
NAME
	void WorldMap::ClearWorldMap()

DESCRIPTION
	This function will properly deallocate all memory being used for the world
	map and assigns each tile to NULL so that it is uninitialized.

AUTHOR
	Austin Rafuls

DATE
	6:57pm 8/28/2019
*/
void WorldMap::ClearWorldMap()
{
	// Delete the entire world map
	for (size_t x = 0; x < m_worldSizeCap.x; x++)
	{
		for (size_t y = 0; y < m_worldSizeCap.y; y++)
		{
			for (size_t z = 0; z < m_layers; z++)
			{
				delete m_worldMap[x][y][z];
				m_worldMap[x][y][z] = NULL;
			}
			m_worldMap[x][y].clear();
		}
		m_worldMap[x].clear();
	}
	m_worldMap.clear();
}



WorldMap::WorldMap(float a_worldGridSize, unsigned int a_width, unsigned int a_height, std::string a_file)
{
	// Set max size of the world
	m_worldSizeCap.x = a_width;
	m_worldSizeCap.y = a_height;
	m_layers = 1;

	// Set size of the world grid
	m_worldGridSizeF = a_worldGridSize;
	m_worldGridSizeU = static_cast<unsigned int>(m_worldGridSizeF);

	// Save textures to save file
	m_textureFile = a_file;

	// Initialize the world map by pushing in empty tiles into 3D vector
	m_worldMap.resize(m_worldSizeCap.x, std::vector <std::vector <Tile*> >());
	for (size_t x = 0; x < m_worldSizeCap.x; x++)
	{
		//m_worldMap.push_back(std::vector <std::vector <Tile*> >());

		for (size_t y = 0; y < m_worldSizeCap.y; y++)
		{
			m_worldMap[x].resize(m_worldSizeCap.y, std::vector <Tile*>());
			//m_worldMap[x].push_back(std::vector <Tile*>());

			for (size_t z = 0; z < m_layers; z++)
			{
				m_worldMap[x][y].resize(m_layers, NULL);
				//m_worldMap[x][y].push_back(NULL);
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

	// DEBUG 
	if (!m_tileTextures.loadFromFile(a_file))
	{
		throw("Error: Could not load texture file for the World Map!");
	}
}



WorldMap::~WorldMap()
{
	ClearWorldMap();
}


/*
NAME
	sf::Texture * WorldMap::GetTileTextures()

DESCRIPTION
	This function is a getter function to fetch the current texture sheet being 
	used.

RETURNS
	sf::Texture pointer to the current texture sheet being used.

AUTHOR
	Austin Rafuls

DATE
	2:10pm 8/23/2019
*/
sf::Texture * WorldMap::GetTileTextures()
{
	return &m_tileTextures;
}


/*
NAME
	void WorldMap::AddTile()

SYNOPSIS
	const unsigned int a_x	- X coordinate
	const unsigned int a_y	- Y coordinate
	const unsigned int a_z	- Z coordinate

DESCRIPTION
	This function will allow the user to place a tile onto the world map in 
	editor mode. The tile will be placed at the mouse coordinates _IF_ the 
	coordinates are within the world map vector.

AUTHOR
	Austin Rafuls

DATE
	8:49pm 8/23/2019
*/
void WorldMap::AddTile(
	const unsigned int a_x, 
	const unsigned int a_y, 
	const unsigned int a_z, 
	sf::IntRect& a_textureRect
)
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
					a_x,					// x
					a_y,					// y
					m_worldGridSizeF,		// z
					m_tileTextures,			// tile texture
					a_textureRect,			// texture rectangle
					0,						// tile type
					false					// tile collision
				);
		}
	}
}


/*
NAME
	void WorldMap::RemoveTile()

SYNOPSIS
	const unsigned int a_x	- X coordinate
	const unsigned int a_y	- Y coordinate
	const unsigned int a_z	- Z coordinate

DESCRIPTION
	This function will allow the user to remove a tile from the world map in
	editor mode. The tile will be removed at the mouse coordinates _IF_ the
	coordinates are within the world map vector and the tile is not NULL.

AUTHOR
	Austin Rafuls

DATE
	12:13pm 8/23/2019
*/
void WorldMap::RemoveTile(const unsigned int a_x, const unsigned int a_y, const unsigned int a_z)
{
	// If the desired tile location is within the world map
	if ((a_x >= 0 && a_x < m_worldSizeCap.x) &&
		(a_y >= 0 && a_y < m_worldSizeCap.y) &&
		(a_z >= 0 && a_z < m_layers))
	{
		// If the desired tile is already claimed
		if (m_worldMap[a_x][a_y][a_z] != NULL)
		{
			// Remove the tile at this position and set to NULL
			delete m_worldMap[a_x][a_y][a_z];
			m_worldMap[a_x][a_y][a_z] = NULL;	// IMPORTANT!! We are always checking for NULL.
		}
	}
}


/*
NAME
	void WorldMap::SaveWorldMap()

SYNOPSIS
	const std::string a_file	- File name to save as

DESCRIPTION
	This function will save the current WorldMap to a text file.

AUTHOR
	Austin Rafuls

DATE
	11:13am 8/28/2019
*/
void WorldMap::SaveWorldMap(const std::string a_file)
{
	std::ofstream ofile;
	ofile.open(a_file);

	if (ofile.is_open())
	{
		// Save base information
		ofile << m_worldSizeCap.x << ' ' << m_worldSizeCap.y << '\n'
			<< m_worldGridSizeU << '\n'
			<< m_layers << '\n'
			<< m_textureFile << '\n';

		// Save ALL tile information
		for (size_t x = 0; x < m_worldSizeCap.x; x++)
		{
			for (size_t y = 0; y < m_worldSizeCap.y; y++)
			{
				for (size_t z = 0; z < m_layers; z++)
				{
					// If not NULL
					if (m_worldMap[x][y][z]) 
					{
						// TODO: Make sure this trailing space is not saved or does not cause problems loading.
						ofile << x << ' ' << y << ' ' << z << ' ' << m_worldMap[x][y][z]->GetAsString() << ' ';
					}
				}
			}
		}

		//
	}
	else
	{
		throw("ERROR: Could not open save file target for writing!");
	}
}


/*
NAME
	void WorldMap::LoadWorldMap()

SYNOPSIS
	const std::string a_file	- File name to load from

DESCRIPTION
	This function will load the WorldMap from a saved text file.

RETURNS
	A boolean value representing of the file was successfully loaded or not.

AUTHOR
	Austin Rafuls

DATE
	11:05pm 9/2/2019
*/
bool WorldMap::LoadWorldMap(const std::string a_file)
{
	std::ifstream ifile;
	ifile.open(a_file);

	if (ifile.is_open())
	{
		// Init empty world map
		ClearWorldMap();

		// Fetch simple serialized data
		sf::Vector2u size;
		unsigned int gridSizeU = 0;
		unsigned int layers = 0;
		std::string textureFile = "";
		ifile >> size.x >> size.y >> gridSizeU >> layers >> textureFile;

		short int tileType = 0;
		unsigned int x = 0, y = 0, z = 0;
		unsigned int textureRectX = 0, textureRectY = 0;
		bool tileCollision = false;

		// Overwrite with loaded data
		m_worldSizeCap.x = size.x;							// Set max size of the world
		m_worldSizeCap.y = size.y;
		m_layers = layers;
		m_worldGridSizeF = static_cast<float>(gridSizeU);	// Set size of the world grid
		m_worldGridSizeU = gridSizeU;
		m_textureFile = textureFile;						// Set textures

		// Initialize the world map by pushing in empty tiles into 3D vector
		m_worldMap.resize(m_worldSizeCap.x, std::vector <std::vector <Tile*> >());
		for (size_t x = 0; x < m_worldSizeCap.x; x++)
		{
			for (size_t y = 0; y < m_worldSizeCap.y; y++)
			{
				m_worldMap[x].resize(m_worldSizeCap.y, std::vector <Tile*>());
				for (size_t z = 0; z < m_layers; z++)
				{
					m_worldMap[x][y].resize(m_layers, NULL);
				}
			}
		}

		// Check if we can load textures from texture file
		if (!m_tileTextures.loadFromFile(textureFile))
		{
			throw("Error: Could not load texture file for a serialized World Map!");
		}

		// Load all tiles of the world map
		while (ifile >> x >> y >> z >> textureRectX >> textureRectY >> tileCollision >> tileType)
		{
			m_worldMap[x][y][z] 
				= new Tile(
					x, y, m_worldGridSizeF, 
					m_tileTextures, 
					sf::IntRect(textureRectX, textureRectY, gridSizeU, gridSizeU),
					tileType,
					tileCollision
				);
		}

		return true;
	}
	else
	{
		//throw("ERROR: Could not open save file target for reading!");
		return false;
	}
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
