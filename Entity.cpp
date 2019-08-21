#include "stdafx.h"
#include "Entity.h"


/*
NAME
	void Game::InitSettings()

DESCRIPTION
	This function will Initialize sprite data upon instantiation.

AUTHOR
	Austin Rafuls

DATE
	5:37pm 8/2/2019
*/
void Entity::InitSettings()
{
	m_mspd = NULL;
	m_animation = NULL;
	m_hitbox = NULL;
}


Entity::Entity()
{
	InitSettings();
}


Entity::~Entity()
{
	// We do not need to delete m_texture because it is an outside resource!
	delete m_mspd;
	delete m_animation;
	delete m_hitbox;
}


/*
NAME
	void Entity::SetMoveSpeed(const float a_veloc)

SYNOPSIS
	const float a_veloc	- Desired movement speed

DESCRIPTION
	This function will create a Movement object to control the entity's 
	movement speed. The a_veloc will determine the velocity.

AUTHOR
	Austin Rafuls

DATE
	8:10am 8/5/2019
*/
void Entity::SetMoveSpeed(const float a_veloc, const float a_accel, const float a_decel)
{
	m_mspd = new Movement(m_sprite, a_veloc, a_accel, a_decel);
}

/*
NAME
	void Entity::CreateSprite(sf::Texture * texture)

SYNOPSIS
	sf::Texture * texture	- Texture to be used for our sprite

DESCRIPTION
	This function will assign our sprite a texture.

AUTHOR
	Austin Rafuls

DATE
	3:46pm 8/2/2019
*/
void Entity::SetTexture(sf::Texture& a_texture)
{
	// a_texture changed to reference so that you cannot send in a null texture
	m_sprite.setTexture(a_texture);
}


/*
NAME
	void Entity::SetAnimation(sf::Sprite & a_sprite, sf::Texture a_texture)

SYNOPSIS
	sf::Texture * texture	- Texture to be used for our sprite

DESCRIPTION
	This function will animate a_sprite using a_texture.

AUTHOR
	Austin Rafuls

DATE
	6:11pm 8/5/2019
*/
void Entity::SetAnimation(sf::Texture a_textureSheet)
{
	m_animation = new Animation(m_sprite, a_textureSheet);
}


/*
NAME
	void Entity::SetHitbox(sf::Sprite & a_sprite)

SYNOPSIS
	sf::Sprite & a_sprite	- The current sprite to attach a hitbox to

DESCRIPTION
	This function will attach a hitbox to a_sprite

AUTHOR
	Austin Rafuls

DATE
	1:52pm 8/7/2019
*/
void Entity::SetHitbox(
	sf::Sprite & a_sprite, 
	float a_offsetX, float a_offsetY,
	int a_width, int a_height)
{
	m_hitbox = new Hitbox(a_sprite, a_offsetX, a_offsetY, a_width, a_height);
}


/*
NAME
	void Entity::Move(const float& a_dt, const float a_x, const float a_y)

SYNOPSIS
	const float& a_dt	- Deltatime
	const float a_x		- Change in the X axis
	const float a_y		- Change in the Y axis

DESCRIPTION
	This function will determine the new location of an entity and move it
	based on the entity's movement speed.

AUTHOR
	Austin Rafuls

DATE
	4:10pm 8/2/2019
*/
void Entity::Move(const float& a_dt, const float a_x, const float a_y)
{
	// Must have an active entity with an active movement component
	if (m_mspd)
	{
		m_mspd->Move(a_dt, a_x, a_y);	// Sets the velocity
	}
}


/*
NAME
	void Entity::SetPosition(const float a_x, const float a_y)

SYNOPSIS
	const float a_x	- X coordinate
	const float a_y	- Y coordinate

DESCRIPTION
	This function will assign an entity to a specified located based off the 
	passed parameters.

AUTHOR
	Austin Rafuls

DATE
	3:50pm 8/2/2019
*/
void Entity::SetPos(const float a_x, const float a_y)
{
	m_sprite.setPosition(a_x, a_y);

	/*
	if (m_sprite)
	{
		m_sprite->setPosition(a_x, a_y);
	}
	*/
}


/*
NAME
	void Entity::Update(const float & a_dt)

SYNOPSIS
	const float & a_dt	- Deltatime

DESCRIPTION
	

AUTHOR
	Austin Rafuls

DATE
	8:01am 8/5/2019
*/
void Entity::Update(const float & a_dt)
{
	// Inherited by player class

	if (m_mspd)
	{
		m_mspd->Update(a_dt);
	}

}


/*
NAME
	void Entity::Render(sf::RenderTarget* a_target)

SYNOPSIS
	sf::RenderTarget* a_target	- The current window to draw to.

DESCRIPTION
	This function will draw onto the window features of the main menu such as
	the background, button, and anything else that might be required.

AUTHOR
	Austin Rafuls

DATE
	3:51pm 8/2/2019
*/
void Entity::Render(sf::RenderTarget& a_target)
{
	a_target.draw(m_sprite);

	if (m_hitbox)
	{
		m_hitbox->Render(a_target);
	}
}
