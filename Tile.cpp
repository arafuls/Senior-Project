#include "stdafx.h"
#include "Tile.h"



Tile::Tile()
{
	m_tileType = 0;
	m_tileCollision = false;
}



Tile::Tile(unsigned int a_x, unsigned int a_y, float a_gridSize, sf::Texture& a_texture, sf::IntRect a_textureRect, short a_tileType, bool a_tileCollision)
{
	m_tile.setPosition(a_x * a_gridSize, a_y * a_gridSize);
	m_tile.setSize(sf::Vector2f(a_gridSize, a_gridSize));
	m_tile.setTexture(&a_texture);
	m_tile.setTextureRect(a_textureRect);
	m_tileType = a_tileType;
	m_tileCollision = a_tileCollision;

	// Outline Demo
	//m_tile.setFillColor(sf::Color::Green);
	//m_tile.setOutlineThickness(1.f);
	//m_tile.setOutlineColor(sf::Color::Red);
}



Tile::~Tile()
{
}


/*
NAME
	const std::string Tile::GetAsString() const

DESCRIPTION
	This function will return the current tile as serialized data.

	Note: Does not end with any padding!

RETURNS
	Returns a const std::string containing all of the tile data.

AUTHOR
	Austin Rafuls

DATE
	8:42pm 8/23/2019
*/
const std::string Tile::GetAsString() const
{
	std::stringstream ss;

	ss << m_tile.getTextureRect().left << " "
		<< m_tile.getTextureRect().top << " "
		<< m_tileCollision << " "
		<< m_tileType;

	return ss.str();
}


/*
NAME
	void WorldMap::Update()

DESCRIPTION
	This function will update the current tile for any changes.

AUTHOR
	Austin Rafuls

DATE
	12:45pm 8/9/2019
*/
void Tile::Update()
{
}


/*
NAME
	void Tile::Render()

SYNOPSIS
	sf::RenderTarget* a_target	- The current window to draw to.

DESCRIPTION
	This function will render the current tile, m_tile, onto the screen for the
	WorldMap class.

AUTHOR
	Austin Rafuls

DATE
	12:44pm 8/9/2019
*/
void Tile::Render(sf::RenderTarget & a_target)
{
	a_target.draw(m_tile);
}
