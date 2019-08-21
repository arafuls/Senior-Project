#include "stdafx.h"
#include "Movement.h"



Movement::Movement(sf::Sprite& a_sprite, float a_mspd, float a_accel, float a_decel)
	: m_sprite(a_sprite), m_maxSpeed(a_mspd), m_accel(a_accel), m_decel(a_decel)
{
	/* DESIGN NOTE
	   You cannot send in null to a reference. This forces the movement 
	   component to be dependant on having a sprite!					*/

	//m_mspd = a_mspd;
}


Movement::~Movement()
{
}



/*
NAME
	const sf::Vector2f & Movement::GetVeloc()

DESCRIPTION
	This function is an accessor to get the current entity's velocity.

RETURNS
	const sf::Vector2f &	- The current entity's velocity.

AUTHOR
	Austin Rafuls

DATE
	3:20pm 8/2/2019
*/
const sf::Vector2f & Movement::GetVeloc()
{
	return m_veloc;
}


/* DEPRECATED FUNCTIONS UNTIL ANIMATION IS WORKING */
/*
NAME
	const bool Movement::GetStatus(const unsigned a_status) const

SYNOPSIS
	const unsigned a_status	- 

DESCRIPTION
	This function is used to determine how the sprite should be animated based
	on which direction it is moving.

	This was originally designed to work with animations to determine if it
	should perform the idle animation or movement animation but as of 8/7/2019
	animations are not currently working.

RETURNS
	const bool	- Represents if the current entity is idle.

AUTHOR
	Austin Rafuls

DATE
	12:16pm 8/7/2019
*/
const bool Movement::GetStatus(const unsigned a_status) const
{
	switch (a_status)
	{
	case IDLE:
		if (m_veloc.x == 0.f && m_veloc.y == 0.f)
		{
			return true;
		}
		break;

	case MOVING:
		if (m_veloc.x != 0.f || m_veloc.y != 0.f)
		{
			return true;
		}
		break;

	case LEFT:
		if (m_veloc.x < 0.f)
		{
			return true;
		}
		break;

	case RIGHT:
		if (m_veloc.x > 0.f)
		{
			return true;
		}
		break;

	case UP:
		if (m_veloc.y < 0.f)
		{
			return true;
		}
		break;

	case DOWN:
		if (m_veloc.y > 0.f)
		{
			return true;
		}
		break;
	}
	return false;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * */



/*
NAME
	void Movement::Move(const float a_x, const float a_y)

SYNOPSIS
	const float a_dt	- Deltatime
	const float a_x		- Direction entity is moving in the X axis.
	const float a_y		- Direction entity is moving in the Y axis.

DESCRIPTION
	This function will accelerate the entity's velocity based on the passed
	parameters until it reaches the maximum velocity, then it will be capped.

AUTHOR
	Austin Rafuls

DATE
	8:19am 8/5/2019
*/
void Movement::Move(const float a_dt, const float a_x, const float a_y)
{
	m_veloc.x += m_accel * a_x;		// Sets x velocity
	m_veloc.y += m_accel * a_y;		// Sets y velocity
}


/*
NAME
	void Movement::Update(const float & a_dt)

SYNOPSIS
	const float a_dt	- Deltatime

DESCRIPTION
	This function will have a constant deceleration. This is to add some
	physics to mimic friction by constantly decelerating.

AUTHOR
	Austin Rafuls

DATE
	8:36pm 8/5/2019
*/
void Movement::Update(const float & a_dt)
{
	// If moving right
	if (0.f < m_veloc.x)
	{
		// If moving faster than max speed
		if (m_veloc.x > m_maxSpeed) { m_veloc.x = m_maxSpeed; }

		// Constant Deceleration
		m_veloc.x -= m_decel;

		// If not moving, don't move
		if (0.f >= m_veloc.x) { m_veloc.x = 0.f; }
	}
	// If moving left
	else if (0.f > m_veloc.x)
	{
		// If moving faster than max speed
		if (m_veloc.x < (m_maxSpeed * -1)) { m_veloc.x = (m_maxSpeed * -1); }

		// Constant Deceleration
		m_veloc.x += m_decel;

		// If not moving, don't move
		if (0.f <= m_veloc.x) { m_veloc.x = 0.f; }
	}

	// If moving up
	if (0.f < m_veloc.y)
	{
		// If moving faster than max speed
		if (m_veloc.y > m_maxSpeed) { m_veloc.y = m_maxSpeed; }

		// Constant Deceleration
		m_veloc.y -= m_decel;

		// If not moving, don't move
		if (0.f >= m_veloc.y) { m_veloc.y = 0.f; }
	}
	// If moving down
	else if (0.f > m_veloc.y)
	{
		// If moving faster than max speed
		if (m_veloc.y < (m_maxSpeed * -1)) { m_veloc.y = (m_maxSpeed * -1); }

		// Constant Deceleration
		m_veloc.y += m_decel;

		// If not moving, don't move
		if (0.f <= m_veloc.y) { m_veloc.y = 0.f; }
	}

	// Commit movement
	m_sprite.move(m_veloc * a_dt);	// Uses the velocity
}
