#include "stdafx.h"
#include "PauseMenu.h"


PauseMenu::PauseMenu(sf::RenderWindow & a_window, sf::Font & a_font)
	: m_font(a_font)
{
	// Font & Text
	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(64);
	m_text.setString("GAME PAUSED");
	m_text.setPosition
	(
		m_container.getPosition().x + 18.f,
		m_container.getPosition().y
	);

	// Background
	m_bg.setFillColor(sf::Color(20, 20, 20, 100));
	m_bg.setSize(
		sf::Vector2f(
			static_cast<float>(a_window.getSize().x), 
			static_cast<float>(a_window.getSize().y)
		)
	);

	// Container
	m_container.setFillColor(sf::Color(20, 20, 20, 200));
	m_container.setSize(
		sf::Vector2f(
			static_cast<float>(a_window.getSize().x) / 4.f,
			static_cast<float>(a_window.getSize().y) * 0.6f
		)
	);
	m_container.setPosition(
		static_cast<float>(a_window.getSize().x) / 2.f - m_container.getSize().x / 2.f, 
		static_cast<float>(a_window.getSize().y) * 0.2f);
}


PauseMenu::~PauseMenu()
{
	// Delete buttons
	auto button = m_buttons.begin();
	for (button = m_buttons.begin(); button != m_buttons.end(); button++)
	{
		delete button->second;
	}
}


/*
NAME
	std::map<std::string, Button*>& PauseMenu::m_getButtons()

DESCRIPTION
	This is a simple accessor function to get all of the buttons used within
	the pause menu.

RETURNS
	Returns a reference to the map of buttons so that we are not copying large
	objects.

AUTHOR
	Austin Rafuls

DATE
	10:42am 8/8/2019
*/
std::map<std::string, gui::Button*>& PauseMenu::m_getButtons()
{
	return m_buttons;
}


/*
NAME
	const bool PauseMenu::IsPressed()

SYNOPSIS
	const std::string a_key	- The key of the button currently being pressed

DESCRIPTION
	This is a simple accessor function to check whether or not the button
	with the key /a_key/ is being pressed.

RETURNS
	Returns a const boolean representing if a button has been pressed.

AUTHOR
	Austin Rafuls

DATE
	11:14am 8/8/2019
*/
const bool PauseMenu::IsPressed(const std::string a_key)
{
	return m_buttons[a_key]->IsPressed();
}


/*
NAME
	void PauseMenu::AddButton()

SYNOPSIS
	const std::string a_key		- The key for our button within the map
	const std::string a_text	- Text for the button to present to the user
	float a_x, float a_y		- The (x,y) coordings to position the button

DESCRIPTION
	This functions allows the programmer to easily add new buttons to the pause
	menu.

AUTHOR
	Austin Rafuls

DATE
	10:42am 8/8/2019
*/
void PauseMenu::AddButton(const std::string a_key, const std::string a_text, float a_y)
{
	// Standard Button Shape and X-Axis Pos
	int width = 250;
	int height = 50;
	float x = m_container.getPosition().x + m_container.getSize().x / 2.f - static_cast<float>(width) / 2.f;

	m_buttons[a_key] = new gui::Button(
		x, a_y, width, height,
		&m_font, 26, a_text,
		sf::Color::White, sf::Color::Red, sf::Color::Transparent,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 150));
}


/*
NAME
	void PauseMenu::Update()

SYNOPSIS
	const sf::Vector2f& a_mousePos	- The current location of the user's cursor

DESCRIPTION
	This function will call each button's respective update method to see if
	the user is interacting with them during the pause menu.

AUTHOR
	Austin Rafuls

DATE
	10:53am 8/8/2019
*/
void PauseMenu::Update(const sf::Vector2f& a_mousePos)
{
	for (auto &button : m_buttons)
	{
		button.second->Update(a_mousePos);
	}
}


/*
NAME
	void PauseMenu::Render(sf::RenderTarget & a_target)

SYNOPSIS
	sf::RenderTarget* a_target	- The current window to draw to.

DESCRIPTION
	This function will draw onto the window features of the pause menu such as
	the background, button, and anything else that might be required.

AUTHOR
	Austin Rafuls

DATE
	3:57pm 8/7/2019
*/
void PauseMenu::Render(sf::RenderTarget & a_target)
{
	a_target.draw(m_bg);
	a_target.draw(m_container);

	// Draw text
	a_target.draw(m_text);

	// Draw all buttons
	for (auto & button : m_buttons)
	{
		button.second->Render(a_target);
	}
}
