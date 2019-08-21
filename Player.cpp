#include "stdafx.h"
#include "Player.h"


// TODO: Documentation
void Player::InitSettings()
{
}


// TODO: Documentation
void Player::InitComp()
{
}


Player::Player(sf::Texture& a_textureSheet, float a_x, float a_y)
{
	//InitSettings();
	//InitComp();

	SetPos(a_x, a_y);
	SetTexture(a_textureSheet);
	SetHitbox(
		m_sprite, 
		0.f, 0.f, 
		static_cast<int>(m_sprite.getGlobalBounds().width), 
		static_cast<int>(m_sprite.getGlobalBounds().height)
	);
	SetMoveSpeed(300.f, 15.f, 5.f);

	/* Can't figure out how to animate so this is now deprecated. */
	//SetAnimation(a_textureSheet);

	//m_animation->AddAnimation(100.f, 0, 0, 13, 0, 192, 192, "IDLE");
}


Player::~Player()
{

}


/*
NAME
	void Player::Update(const float a_dt)

SYNOPSIS
	const float a_dt	- Delta time

DESCRIPTION
	This function will call respective update methods from objects used by an 
	entity such as Movement.

AUTHOR
	Austin Rafuls

DATE
	2:46pm 8/7/2019
*/
void Player::Update(const float a_dt)
{
	//Entity::Update(a_dt);
	m_mspd->Update(a_dt);
	m_hitbox->Update();


	/* DEPRECATED UNTIL ANIMATION IS WORKING 
	if (m_mspd->GetStatus(IDLE))
	{
		//m_animation->Play(a_dt, "PLAYER_IDLE");
	}*/

	if (m_mspd->GetStatus(LEFT))
	{
		// Flip sprite to face left
		m_sprite.setOrigin(0.f, 0.f);
		m_sprite.setScale(1.f, 1.f);
	}
	if (m_mspd->GetStatus(RIGHT))
	{
		// Flip sprite to face right
		m_sprite.setOrigin(100.f, 0.f);
		m_sprite.setScale(-1.f, 1.f);
	}
}
