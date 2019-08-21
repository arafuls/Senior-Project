#include "stdafx.h"
#include "Animation.h"


Animation::Animation(sf::Sprite& a_sprite, sf::Texture& a_textureSheet)
	:m_sprite(a_sprite), m_textureSheet(a_textureSheet)
{
	m_sprite = a_sprite;
	m_textureSheet = a_textureSheet;
}


Animation::~Animation()
{
	// Delete all animation ptrs
	for (auto &anim : m_animations)
	{
		delete anim.second;
	}
}

void Animation::AddAnimation(
	float a_animationTimer,
	int a_startFrameX, int a_startFrameY, int a_framesX, int a_framesY,
	int a_width, int a_height,
	const std::string a_key)
{
	m_animations[a_key] = new Anim(
		m_sprite, m_textureSheet, 
		a_animationTimer, 
		a_startFrameX, a_startFrameY, a_framesX, a_framesY, 
		a_width, a_height);
}

void Animation::Play(const float &a_dt, const std::string a_key)
{
	m_animations[a_key]->Play(a_dt);
}

Animation::Anim::Anim(
	sf::Sprite& a_sprite, sf::Texture& a_textureSheet,
	float a_animationTimer,
	int a_startFrameX, int a_startFrameY, int a_framesX, int a_framesY,
	int a_width, int a_height)
	: m_sprite(a_sprite), m_textureSheet(a_textureSheet), m_width(a_width), m_height(a_height), m_animationTimer(a_animationTimer)
{
	// Select the size of our frame for each animation
	m_startRect = sf::IntRect(a_startFrameX * a_width, a_startFrameY * a_height, a_width, a_height);
	m_endRect = sf::IntRect(a_framesX * a_width, a_framesY * a_height, a_width, a_height);
	m_curRect = m_startRect;

	// Select the first frame of the animation
	m_sprite.setTexture(m_textureSheet, true);
	m_sprite.setTextureRect(m_startRect);
}

void Animation::Anim::Play(const float & a_dt)
{
	// Update timer
	m_timer += 10.f * a_dt;

	// if timer is at or goes past the upper bound
	if (m_timer >= m_animationTimer)
	{
		// Reset timer
		m_timer = 0.f;

		// if havent reached last animation
		if (m_curRect != m_endRect)
		{
			// Animate by moving to the right on textureSheet
			m_curRect.left += m_width;
		}
		else // Otherwise, reset
		{
			m_curRect.left = m_startRect.left;
		}

		m_sprite.setTextureRect(m_curRect);
	}
}

void Animation::Anim::Reset()
{
	m_timer = 0.f;
	m_curRect = m_startRect;
}
