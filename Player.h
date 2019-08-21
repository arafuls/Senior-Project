#pragma once
#include "Entity.h"

class Player :
	public Entity
{
private:

	void InitSettings();
	void InitComp();

public:
	Player(sf::Texture& a_texture, float a_x, float a_y);
	virtual ~Player();

	virtual void Update(const float a_dt);
};

