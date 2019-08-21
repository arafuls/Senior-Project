#pragma once

class Animation
{
private:
	class Anim
	{
	public:
		sf::Sprite& m_sprite;
		sf::Texture& m_textureSheet;
		sf::IntRect m_startRect;
		sf::IntRect m_endRect;
		sf::IntRect m_curRect;
		float m_timer;
		float m_animationTimer;
		int m_width;
		int m_height;

		Anim(sf::Sprite& a_sprite, sf::Texture& a_textureSheet, 
			float a_animationTimer, 
			int a_startFrameX, int a_startFrameY, int a_framesX, int a_framesY,
			int a_width, int a_height);

		//void Play();
		//void Pause();
		//void Restart();

		void Play(const float& a_dt);
		void Reset();
	};

	sf::Sprite& m_sprite;
	sf::Texture& m_textureSheet;
	std::map<std::string, Anim*> m_animations;

public:
	Animation(sf::Sprite& a_sprite, sf::Texture& a_textureSheet);
	virtual ~Animation();

	void AddAnimation(
		float a_animationTimer,
		int a_startFrameX, int a_startFrameY, int a_framesX, int a_framesY,
		int a_width, int a_height, 
		const std::string a_key);
	//void StartAnimation(const std::string a_animation);
	//void PauseAnimation(const std::string a_animation);
	//void ResetAnimation(const std::string a_animation);
	void Play(const float& a_dt, const std::string a_key);
};

