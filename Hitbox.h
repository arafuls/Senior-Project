#pragma once

class Hitbox
{
private:
	sf::Sprite& m_sprite;			// Force sprite in order to have a hitbox
	sf::RectangleShape m_hitbox;	// Design note in implementation
	float m_offsetX;
	float m_offsetY;

public:
	Hitbox(
		sf::Sprite& a_sprite, 
		float a_offsetX, float a_offsetY, 
		int a_width, int a_height);
	virtual ~Hitbox();

	bool CheckCollision(const sf::FloatRect& a_rect);

	void Update();
	void Render(sf::RenderTarget& a_target);
};

