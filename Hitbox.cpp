#include "stdafx.h"
#include "Hitbox.h"



Hitbox::Hitbox(
	sf::Sprite& a_sprite, 
	float a_offsetX, float a_offsetY, 
	int a_width, int a_height)
	: m_sprite(a_sprite), m_offsetX(a_offsetX), m_offsetY(a_offsetY)
{
	/* DESIGN NOTE
		Using a RectangleShape instead of IntRect because you cannot draw 
		IntRect to the screen which I may want to do for debugging purposes. 
		
		RectangleShape also contains a FloatRect within it so it doesn't
		really change much.													*/

	// Assign hitbox to sprite and set size of hitbox
	m_hitbox.setPosition(m_sprite.getPosition().x + a_offsetX, m_sprite.getPosition().y + a_offsetY);
	m_hitbox.setSize(sf::Vector2f(static_cast<float>(a_width), static_cast<float>(a_height)));
	m_hitbox.setFillColor(sf::Color::Transparent);	// No fill
	m_hitbox.setOutlineThickness(1.f);				// Hitbox Outline size
	m_hitbox.setOutlineColor(sf::Color::Red);		// Hitbox Outline color

}



Hitbox::~Hitbox()
{



}


/*
NAME
	bool Hitbox::CheckCollision(const sf::FloatRect a_rect)

SYNOPSIS
	const sf::FloatRect a_rect	- The FloatRect of the current hitbox.

DESCRIPTION
	This function will check to see if an entitiy's hitbox as collided with 
	anything.

RETURNS
	Returns a bool representing if the current entity has collided with 
	something.

AUTHOR
	Austin Rafuls

DATE
	1:47pm 8/7/2019
*/
bool Hitbox::CheckCollision(const sf::FloatRect& a_rect)
{
	return m_hitbox.getGlobalBounds().intersects(a_rect);
}


/*
NAME
	void Hitbox::Update()

DESCRIPTION
	This function will constantly update the hitbox's location so that it is
	attached properly with the sprite's location.

AUTHOR
	Austin Rafuls

DATE
	1:43pm 8/7/2019
*/
void Hitbox::Update()
{
	m_hitbox.setPosition
	(
		m_sprite.getPosition().x + m_offsetX, 
		m_sprite.getPosition().y + m_offsetY
	);
}


/*
NAME
	void Hitbox::Render(sf::RenderTarget & a_target)

SYNOPSIS
	sf::RenderTarget & a_target	- The current window to draw to

DESCRIPTION
	This function will render the hitbox onto the screen, mainly for debugging
	purposes.

AUTHOR
	Austin Rafuls

DATE
	1:45pm 8/7/2019
*/
void Hitbox::Render(sf::RenderTarget & a_target)
{
	a_target.draw(m_hitbox);
}
