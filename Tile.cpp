#include "stdafx.h"
#include "Tile.h"



Tile::Tile()
{
}

Tile::Tile(float a_gridSize, float a_x, float a_y)
{
	m_tile.setPosition(a_x, a_y);
	m_tile.setSize(sf::Vector2f(a_gridSize, a_gridSize));
	
	// DEBUG -- REMOVE LATER
	m_tile.setFillColor(sf::Color::Green);
	m_tile.setOutlineThickness(1.f);
	m_tile.setOutlineColor(sf::Color::Red);
}



Tile::~Tile()
{
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
