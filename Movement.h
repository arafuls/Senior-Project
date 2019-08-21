#pragma once

enum MOVEMENT_STATUS {IDLE = 0, MOVING, LEFT, RIGHT, UP, DOWN};

class Movement
{
private:
	sf::Sprite& m_sprite;	// Force Init references
	sf::Vector2f m_veloc;
	float m_accel;
	float m_decel;
	float m_maxSpeed;

public:
	Movement(sf::Sprite& a_sprite, float a_mspd, float a_accel, float a_decel);
	virtual ~Movement();

	const sf::Vector2f& GetVeloc();

	/* DEPRECATED UNTIL ANIMATION IS WORKING */
	const bool GetStatus(const unsigned a_status) const;
	/* * * * * * * * * * * * * * * * * * * * */

	void Move(const float a_dt, const float a_x, const float a_y);
	void Update(const float& a_dt);
};

