#pragma once
#include "GUI.h"

class PauseMenu
{
private:
	sf::RectangleShape m_bg;
	sf::RectangleShape m_container;
	sf::Font & m_font;
	sf::Text m_text;
	std::map<std::string, gui::Button *> m_buttons;
	


public:
	PauseMenu(sf::RenderWindow & a_window, sf::Font & a_font);
	virtual ~PauseMenu();

	std::map<std::string, gui::Button *>& m_getButtons();

	const bool IsPressed(const std::string a_key);
	void AddButton(const std::string a_key, const std::string a_text, float a_y);
	void Update(const sf::Vector2f& a_mousePos);
	void Render(sf::RenderTarget & a_target);
};

