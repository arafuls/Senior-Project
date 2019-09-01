#include "stdafx.h"
#include "MainMenuState.h"


void MainMenuState::InitSettings()
{

}

/*
NAME
	void MainMenuState::InitFonts()

DESCRIPTION
	This function will Initialize the desired font for the game and throw an
	exception if it could not be loaded.

AUTHOR
	Austin Rafuls

DATE
	8:47am 8/5/2019
*/
void MainMenuState::InitFonts()
{
	if (!m_font.loadFromFile("Fonts/BebasNeue-Regular.ttf"))
	//if (!m_font.loadFromFile("Fonts/Black-Melody.otf"))
	{
		throw("Error: Could not load font BebasNeue-Regular.ttf");
	}
}


/*
NAME
	void MainMenuState::InitKeybindings()

DESCRIPTION
	This function will Initialize the desired key bindings for the main menu
	game state by overwriting them from an ini file.

AUTHOR
	Austin Rafuls

DATE
	2:51am 7/30/2019
*/
void MainMenuState::InitKeybindings()
{
	// NOTE: Map removes duplicates for you, no need to check.
	std::ifstream keycfg("Config/mainmenu_binds.ini");

	if (keycfg.is_open())
	{
		std::string key = "";
		std::string keyvalue = "";

		while (keycfg >> key >> keyvalue)
		{
			m_keybindings[key] = m_suppKeys->at(keyvalue);
		}
	}
	keycfg.close();

	//m_keybindings.emplace("MOVE_UP", m_suppKeys->at("W"));
	//if(m_keybindings["MOVE_UP"]) { key exists }
}


/*
NAME
	void MainMenuState::InitGUI()

DESCRIPTION
	This function will Initialize the Graphical User Interface for the main
	menu, specifically the interactable buttons.

AUTHOR
	Austin Rafuls

DATE
	6:05am 8/5/2019
*/
void MainMenuState::InitGUI()
{
	m_buttons["START_GAME"] = new gui::Button(
		80.f, 100.f, 250, 50,
		&m_font, 26, "New Game",
		sf::Color::White, sf::Color::Yellow, sf::Color::Transparent,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 150));


	m_buttons["OPTIONS"] = new gui::Button(
		80.f, 200.f, 250, 50,
		&m_font, 26, "Options",
		sf::Color::White, sf::Color::Yellow, sf::Color::Transparent,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 150));

	m_buttons["EDIT_GAME"] = new gui::Button(
		80.f, 300.f, 250, 50,
		&m_font, 26, "Edit Game",
		sf::Color::White, sf::Color::Yellow, sf::Color::Transparent,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 150));

	m_buttons["EXIT_GAME"] = new gui::Button(
		80.f, 500.f, 250, 50,
		&m_font, 26, "Quit Game",
		sf::Color::White, sf::Color::Yellow, sf::Color::Transparent,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 150));
}


/*
NAME
	void MainMenuState::InitBG()

DESCRIPTION
	This function will Initialize the background image for the main menu.

AUTHOR
	Austin Rafuls

DATE
	6:48pm 8/1/2019
*/
void MainMenuState::InitBG()
{
	// Set the size of our background image
	m_bg.setSize(
		sf::Vector2f(
			static_cast<float>(m_window->getSize().x), 
			static_cast<float>(m_window->getSize().y)
		)
	);

	// Load and set the background texture from file
	if (!m_bgtexture.loadFromFile("Resources/Images/Backgrounds/Knight.jpg"))
	{
		// Set background solid color if could not load image
		m_bg.setSize(
			sf::Vector2f(
				static_cast<float>(m_window->getSize().x), 
				static_cast<float>(m_window->getSize().y)
			)
		);
		m_bg.setFillColor(sf::Color::Cyan);

		//throw("Error: Could not load background texture!");
	}
	m_bg.setTexture(&m_bgtexture);
}



MainMenuState::MainMenuState(StateDataContainer * a_stateData)
	: State(a_stateData)
{
	InitSettings();
	InitFonts();
	InitKeybindings();
	InitGUI();
	InitBG();
}



MainMenuState::~MainMenuState()
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
	void MainMenuState::UpdateGUI()

DESCRIPTION
	This function will update the GUI and handle their functionality.

AUTHOR
	Austin Rafuls

DATE
	8:23pm 8/9/2019
*/
void MainMenuState::UpdateGUI()
{
	for (auto &button : m_buttons)
	{
		button.second->Update(m_mousePosCam);
	}

	// New Game
	if (m_buttons["START_GAME"]->IsPressed())
	{
		m_states->push(new GameState(m_stateData));
	}

	// Settings
	if (m_buttons["OPTIONS"]->IsPressed())
	{
		m_states->push(new Settings(m_stateData));
	}

	// Editor
	if (m_buttons["EDIT_GAME"]->IsPressed())
	{
		m_states->push(new Editor(m_stateData));
	}

	// Exit
	if (m_buttons["EXIT_GAME"]->IsPressed())
	{
		EndState();
	}
}


/*
NAME
	void MainMenuState::Update(const float& a_dt)

SYNOPSIS
	const float& a_dt	- Deltatime

DESCRIPTION
	This function will constantly loop to update the main menu's gui and state
	status.

AUTHOR
	Austin Rafuls

DATE
	2:53am 7/30/2019
*/
void MainMenuState::Update(const float& a_dt)
{
	UpdateMousePos();
	UpdateKeys(a_dt);
	UpdateGUI();

	// DEBUG
	system("cls");
	//std::cout << m_mousePosCam.x << " " << m_mousePosCam.y << std::endl;
}


/*
NAME
	void MainMenuState::RenderGUI()

DESCRIPTION
	This function will iterate through all buttons in the map and render them.

AUTHOR
	Austin Rafuls

DATE
	3:53pm 7/30/2019
*/
void MainMenuState::RenderGUI(sf::RenderTarget & a_target)
{
	for (auto &button : m_buttons)
	{
		button.second->Render(a_target);
	}
}


/*
NAME
	void MainMenuState::Render(sf::RenderTarget* a_target)

SYNOPSIS
	sf::RenderTarget* a_target	- The current window to draw to.

DESCRIPTION
	This function will draw onto the window features of the main menu such as
	the background, button, and anything else that might be required.

AUTHOR
	Austin Rafuls

DATE
	8:15pm 8/1/2019
*/
void MainMenuState::Render(sf::RenderTarget * a_target)
{
	if (!a_target)
	{
		a_target = m_window;
	}

	a_target->draw(m_bg);
	RenderGUI(* a_target);

	// DEBUG : DELETE LATER
	// Shows mouse coordinates for easier button placement

	/*
	sf::Text mt;
	mt.setPosition(m_mousePosCam);
	mt.setFont(m_font);
	mt.setCharacterSize(32);
	std::stringstream ss;
	ss << m_mousePosCam.x << " " << m_mousePosCam.y;
	mt.setString(ss.str());
	a_target->draw(mt);
	*/
}


/*
NAME
	void MainMenuState::UpdateKeys(const float & a_dt)

SYNOPSIS
	const float & a_dt	- Deltatime

DESCRIPTION
	This function will check to see if an exit request was called by the user.

AUTHOR
	Austin Rafuls

DATE
	2:55am 7/30/2019
*/
void MainMenuState::UpdateKeys(const float & a_dt)
{

}