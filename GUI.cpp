#include "stdafx.h"
#include "GUI.h"


gui::Button::Button(
	float a_x, float a_y, int a_w, int a_h,
	sf::Font * a_font, unsigned int a_charSize, std::string a_text,
	sf::Color a_textInactiveColor, sf::Color a_textHoverColor, sf::Color a_textActiveColor,
	sf::Color a_inactiveColor, sf::Color a_hoverColor, sf::Color a_activeColor,
	sf::Color a_outlineInactiveColor,
	sf::Color a_outlineHoverColor,
	sf::Color a_outlineActiveColor,
	unsigned int a_identifier
)
{
	// Set last known button status
	m_identifier = a_identifier;

	// Button is inactive by default
	m_buttonStatus = INACTIVE;

	// Create button at coordinates (x,y) with size (w,h)
	m_button.setPosition(sf::Vector2f(a_x, a_y));
	m_button.setFillColor(a_inactiveColor);
	m_button.setOutlineThickness(1.f);
	m_button.setOutlineColor(a_outlineInactiveColor);
	m_button.setSize(
		sf::Vector2f(
			static_cast<float>(a_w), 
			static_cast<float>(a_h)
		)
	);

	// Font and Text settings
	m_text.setString(a_text);					// Button Text
	m_text.setFillColor(m_textInactiveColor);	// Font Color
	m_text.setCharacterSize(a_charSize);		// Font Size
	m_font = a_font;							// Get Font
	m_text.setFont(* m_font);					// Set Font
	m_text.setPosition(							// Text Position
		m_button.getPosition().x +
			(m_button.getGlobalBounds().width / 2.f) - 
			(m_text.getGlobalBounds().width / 2.f),
		m_button.getPosition().y + 
			(m_button.getGlobalBounds().height / 2.f) - 
			(m_text.getGlobalBounds().height / 2.f)
	);

	// Get text colors
	m_textInactiveColor = a_textInactiveColor;
	m_textHoverColor = a_textHoverColor;
	m_textActiveColor = a_textActiveColor;

	// Get button colors
	m_inactiveColor = a_inactiveColor;
	m_hoverColor = a_hoverColor;
	m_activeColor = a_activeColor;

	// Get outline colors
	m_outlineInactiveColor = a_outlineInactiveColor;
	m_outlineHoverColor = a_outlineHoverColor;
	m_outlineActiveColor = a_outlineActiveColor;

	// Set to inactive color by default
	m_button.setFillColor(m_inactiveColor);	
}


gui::Button::~Button()
{
}


/*
NAME
	const bool Button::isPressed() const

DESCRIPTION
	This function will return a bool determining whether or not the current 
	button has been pressed or not.

RETURNS
	A boolean representing the current status of the button, pressed or 
	not pressed.

AUTHOR
	Austin Rafuls

DATE
	2:43am 7/30/2019
*/
const bool gui::Button::IsPressed() const
{
	if (m_buttonStatus == ACTIVE) 
	{ 
		return true; 
	}
	else 
	{ 
		return false; 
	}
}


/*
NAME
	const unsigned int & gui::Button::GetIdentifier() const

DESCRIPTION
	This function fetch and return the last known identifier for the button.
	m_identifier is used as the index from the last selection made from a 
	button press.

	Default is 0.

RETURNS
	Returns a const unsigned int that is stored within the button class.

AUTHOR
	Austin Rafuls

DATE
	5:07pm 8/8/2019
*/
const unsigned int & gui::Button::GetIdentifier() const
{
	return m_identifier;
}


/*
NAME
	void gui::Button::SetIdentifier()

SYNOPSIS
	const unsigned int a_identifier	- Item index from last buttom press.

DESCRIPTION
	This function will override the current m_identifier variable with the
	unsigned int from the passed parameter a_identifier.

AUTHOR
	Austin Rafuls

DATE
	5:32pm 8/8/2019
*/
void gui::Button::SetIdentifier(const unsigned int a_identifier)
{
	m_identifier = a_identifier;
}


/*
NAME
	const std::string & gui::Button::GetString()

DESCRIPTION
	This function fetch and return the string within the current button object.

RETURNS
	Returns a const string reference that is stored within the button class.

AUTHOR
	Austin Rafuls

DATE
	4:46pm 8/8/2019
*/
const std::string gui::Button::GetString()
{
	return m_text.getString();
}


/*
NAME
	void gui::Button::SetString()

SYNOPSIS
	const std::string a_string	- The text to replace the current button string
									text attribute.

DESCRIPTION
	This function will override the current text within a button object with
	a_string.

AUTHOR
	Austin Rafuls

DATE
	2:21pm 8/8/2019
*/
void gui::Button::SetString(const std::string a_string)
{
	m_text.setString(a_string);
}


/*
NAME
	void Button::Update(sf::Vector2f a_mousePos)

SYNOPSIS
	sf::Vector2f a_mousePos	- The current mouse position in x,y coordinates.

DESCRIPTION
	This function will constantly loop to update the current status of a
	button and will change the button color accordingly.

AUTHOR
	Austin Rafuls

DATE
	10:51am 8/8/2019
*/
void gui::Button::Update(const sf::Vector2f& a_mousePos)
{
	m_buttonStatus = INACTIVE;

	// If button is hovered
	if (m_button.getGlobalBounds().contains(a_mousePos))
	{
		m_buttonStatus = HOVER;

		// If button is clicked
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_buttonStatus = ACTIVE;
		}
	}

	// Change color based on button status
	switch (m_buttonStatus)
	{
	case INACTIVE:
		m_button.setFillColor(m_inactiveColor);
		m_button.setOutlineColor(m_outlineInactiveColor);
		m_text.setFillColor(m_textInactiveColor);
		break;

	case HOVER:
		m_button.setFillColor(m_hoverColor);
		m_button.setOutlineColor(m_outlineHoverColor);
		m_text.setFillColor(m_textHoverColor);
		break;

	case ACTIVE:
		m_button.setFillColor(m_activeColor);
		m_button.setOutlineColor(m_outlineActiveColor);
		m_text.setFillColor(m_textActiveColor);
		break;

	default:
		m_button.setFillColor(sf::Color::Red);
		m_button.setOutlineColor(sf::Color::Yellow);
		m_text.setFillColor(sf::Color::Magenta);
		break;
	}
}


/*
NAME
	void Button::Render(sf::RenderTarget * a_target)

SYNOPSIS
	sf::RenderTarget * a_target	- The window that is being drawn to.

DESCRIPTION
	This function will draw the button with text if added to the current window.

AUTHOR
	Austin Rafuls

DATE
	2:03pm 8/7/2019
*/
void gui::Button::Render(sf::RenderTarget & a_target)
{
	a_target.draw(m_button);
	a_target.draw(m_text);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


gui::DropDownList::DropDownList
(
	float a_x, float a_y,		// (x,y) coordinates of button
	int a_width, int a_height,	// width and height of button
	std::string a_itemList[],	// Button text to display
	sf::Font & a_font,			// Button text font
	unsigned int a_idx,			// Default index of a_itemList[]
	unsigned int a_size			// Number of items in a_itemList[]
)
	: m_dropTimer(0.f), m_dropTimerCap(3.f), m_font(a_font), m_display(false)
{
	// Set current active item to parameter index
	m_activeItem = new gui::Button(
		a_x, a_y, a_width, a_height,
		&m_font, 26, a_itemList[a_idx],
		sf::Color(255, 255, 255, 170), sf::Color(255, 255, 255, 170), sf::Color(255, 255, 255, 170),
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 200),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent
	);

	// Push all items onto list
	for (size_t i = 0; i < a_size; i++)
	{
		m_itemList.push_back(
			new gui::Button(
				a_x, a_y + ((i+1) * a_height) + 0.5f, a_width, a_height,
				&m_font, 26, a_itemList[i],
				sf::Color(255, 255, 255, 170), sf::Color::Yellow, sf::Color::Transparent,
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 150),
				sf::Color::Transparent, sf::Color::Yellow, sf::Color::Green,
				i
			)
		);
	}
}


gui::DropDownList::~DropDownList()
{
	delete m_activeItem;

	for (size_t i = 0; i < m_itemList.size(); i++)
	{
		delete m_itemList[i];
	}
}


/*
NAME
	const bool gui::DropDownList::GetDropTimer()

DESCRIPTION
	This is a simple accessor that will determine if dropdownlist 
	interaction will be recognized depending on the drop timers.

RETURNS
	Returns a boolean representing if the dropdownlist can be shown/hidden.

AUTHOR
	Austin Rafuls

DATE
	2:48m 8/8/2019
*/
const bool gui::DropDownList::GetDropTimer()
{
	if (m_dropTimer >= m_dropTimerCap)
	{
		m_dropTimer = 0.f;
		return true;
	}
	return false;
}


/*
NAME
	void gui::DropDownList::UpdateDropTimer()

SYNOPSIS
	const float a_dt	- Delta time

DESCRIPTION
	This function will update the drop timer over time to prevent spamming.
AUTHOR
	Austin Rafuls

DATE
	2:48pm 8/8/2019
*/
void gui::DropDownList::UpdateDropTimer(const float & a_dt)
{
	if (m_dropTimer < m_dropTimerCap)
	{
		m_dropTimer += 10.f * a_dt;
	}
}


/*
NAME
	const unsigned int & gui::DropDownList::GetActiveElementIdentifier() const

DESCRIPTION
	This function fetch and return the last known identifier for the active.
	element. This is used as the index from the last selection made from a
	selected dropdownlist item.

	Default is 0.

RETURNS
	Returns a const unsigned int that is stored within the button class.

AUTHOR
	Austin Rafuls

DATE
	6:21pm 8/8/2019
*/
const unsigned int & gui::DropDownList::GetActiveElementIdentifier() const
{
	return m_activeItem->GetIdentifier();
}


/*
NAME
	void gui::DropDownList::Update()

SYNOPSIS
	const sf::Vector2f & a_mousePos	- The current mouse position in x,y coordinates.

DESCRIPTION
	This function will call each button's respective update method to see if
	the user is interacting with them during the drop down menu selection.

AUTHOR
	Austin Rafuls

DATE
	5:35pm 8/8/2019
*/
void gui::DropDownList::Update(const sf::Vector2f & a_mousePos, const float & a_dt)
{
	UpdateDropTimer(a_dt);
	m_activeItem->Update(a_mousePos);

	// if allowed to show drop down list
	if (m_activeItem->IsPressed() && GetDropTimer())
	{
		// if already shown
		if (m_display)
		{
			// Hide List
			m_display = false;
		}
		else
		{
			// Show List
			m_display = true;
		}
	}

	// if list is being shown
	if (m_display)
	{
		// update it
		for (auto &item : m_itemList)
		{
			item->Update(a_mousePos);

			// if item is clicked && isn't being spammed
			if (item->IsPressed() && GetDropTimer())
			{
				m_display = false;
				m_activeItem->SetString(item->GetString()); // Set to last selected item
				m_activeItem->SetIdentifier(item->GetIdentifier()); // Save selected items id
			}
		}
	}
}


/*
NAME
	void gui::DropDownList::Render()

SYNOPSIS
	sf::RenderTarget & a_target	- The current window to draw on

DESCRIPTION
	This function will draw onto the window features of the drop down list
	onto the screen.

AUTHOR
	Austin Rafuls

DATE
	2:25pm 8/8/2019
*/
void gui::DropDownList::Render(sf::RenderTarget & a_target)
{
	m_activeItem->Render(a_target);

	if (m_display)
	{
		for (auto &item : m_itemList)
		{
			item->Render(a_target);
		}
	}
}
