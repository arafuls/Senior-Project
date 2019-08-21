#pragma once
#include "Movement.h"
#include "Animation.h"
#include "Hitbox.h"

class Entity
{
private:
	void InitSettings();

protected:
	sf::Sprite m_sprite;
	Movement* m_mspd;
	Animation* m_animation;	// Deprecated
	Hitbox* m_hitbox;

public:
	Entity();
	virtual ~Entity();

	void SetMoveSpeed(const float a_veloc, const float a_accel, const float a_decel);
	void SetTexture(sf::Texture& a_texture);
	void SetAnimation(sf::Texture a_textureSheet);
	void SetHitbox(
		sf::Sprite& a_sprite, 
		float a_offsetX, float a_offsetY,
		int a_width, int a_height);

	virtual void Move(const float& a_dt, const float a_x, const float a_y);
	virtual void SetPos(const float a_x, const float a_y);
	virtual void Update(const float& a_dt);
	virtual void Render(sf::RenderTarget& a_target);
};