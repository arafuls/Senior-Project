#include "stdafx.h"
#include "Editor.h"


// TODO: Documentation
void Editor::InitSettings()
{

}

/*
NAME
	void Editor::InitFonts()

DESCRIPTION
	This function will Initialize the desired font for the game and throw an
	exception if it could not be loaded.

AUTHOR
	Austin Rafuls

DATE
	12:43pm 8/7/2019
*/
void Editor::InitFonts()
{
	if (!m_font.loadFromFile("Fonts/BebasNeue-Regular.ttf"))
	{
		throw("Error: Could not load font BebasNeue-Regular.ttf");
	}
}


/*
NAME
	void Editor::InitKeybindings()

DESCRIPTION
	This function will Initialize the desired key bindings for the editor mode
	game state by overwriting them from an ini file.

AUTHOR
	Austin Rafuls

DATE
	12:43pm 8/7/2019
*/
void Editor::InitKeybindings()
{
	// NOTE: Map removes duplicates for you, no need to check.
	std::ifstream keycfg("Config/editor_binds.ini");

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
}


/*
NAME
	void Editor::InitGUI()

DESCRIPTION
	This function will Initialize the Graphical User Interface for the editor
	mode, specifically the interactable buttons.

AUTHOR
	Austin Rafuls

DATE
	9:05pm 8/9/2019
*/
void Editor::InitGUI()
{
	/*
	m_buttons["START_GAME"] = new Button(
		80, 100, 250, 50,
		&m_font, 26, "New Game",
		sf::Color::White, sf::Color::Red, sf::Color::Transparent,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 150));
	*/
	m_selectionRect.setSize(sf::Vector2f(m_stateData->m_worldGridSize, m_stateData->m_worldGridSize));
	m_selectionRect.setFillColor(sf::Color::Transparent);
	m_selectionRect.setOutlineThickness(1.f);
	m_selectionRect.setOutlineColor(sf::Color::Yellow);
}


/*
NAME
	void Editor::InitPauseMenu()

DESCRIPTION
	This function will initialize the pause menu screen using saved settings
	from the Editor.

AUTHOR
	Austin Rafuls

DATE
	2:18pm 8/9/2019
*/
void Editor::InitPauseMenu()
{
	m_pauseMenu = new PauseMenu(*m_window, m_font);
	m_pauseMenu->AddButton("EXIT_GAME", "Main Menu", 500.f);
}


/*
NAME
	void Editor::InitWorldMap()

DESCRIPTION
	This function will initialize and create the world map with all its tiles.

AUTHOR
	Austin Rafuls

DATE
	8:42pm 8/9/2019
*/
void Editor::InitWorldMap()
{
	m_worldMap = new WorldMap(m_stateData->m_worldGridSize, 10, 10);
}


Editor::Editor(StateDataContainer * a_stateData)
	: State(a_stateData)
{
	InitSettings();
	InitFonts();
	InitKeybindings();
	InitPauseMenu();
	InitGUI();
	InitWorldMap();
}



Editor::~Editor()
{
	auto button = m_buttons.begin();
	for (button = m_buttons.begin(); button != m_buttons.end(); button++)
	{
		delete button->second;
	}

	delete m_pauseMenu;
	delete m_worldMap;
}


/*
NAME
	void Editor::UpdatePauseGUI()

DESCRIPTION
	This function will check to see the user is interacting with the buttons
	within the pause menu and handle their functionality.

AUTHOR
	Austin Rafuls

DATE
	2:24pm 8/9/2019
*/
void Editor::UpdatePauseGUI()
{
	if (m_pauseMenu->IsPressed("EXIT_GAME"))
	{
		EndState();
	}
}


/*
NAME
	void Editor::UpdateGUI()

DESCRIPTION
	This function will update the GUI and handle their functionality. This way
	the game knows if a button is being hovered or is pressed.

AUTHOR
	Austin Rafuls

DATE
	9:29pm 8/9/2019
*/
void Editor::UpdateGUI()
{
	// Update Buttons
	for (auto &button : m_buttons)
	{
		button.second->Update(m_mousePosCam);
	}

	// Update selection rectangle to each grid
	m_selectionRect.setPosition(
		m_mousePosGrd.x * m_stateData->m_worldGridSize,
		m_mousePosGrd.y * m_stateData->m_worldGridSize
	);
}


/*
NAME
	void Editor::Update(const float& a_dt)

SYNOPSIS
	const float& a_dt	- Deltatime

DESCRIPTION
	This function will constantly loop to update the editor mode gui and state
	status.

AUTHOR
	Austin Rafuls

DATE
	9:34pm 8/9/2019
*/
void Editor::Update(const float& a_dt)
{
	UpdateMousePos();
	UpdateInputTimer(a_dt);
	UpdateKeys(a_dt);

	if (m_pause)
	{
		// Paused
		m_pauseMenu->Update(m_mousePosCam);
		UpdatePauseGUI();
	}
	else
	{
		// Unpaused
		UpdateGUI();
		UpdateEditorKeys(a_dt);
	}
}


/*
NAME
	void Editor::RenderGUI()

DESCRIPTION
	This function will iterate through all buttons in the map and render them.

AUTHOR
	Austin Rafuls

DATE
	9:10pm 8/9/2019
*/
void Editor::RenderGUI(sf::RenderTarget & a_target)
{
	// Draw buttons
	for (auto &button : m_buttons)
	{
		button.second->Render(a_target);
	}

	// Draw selection rectangle
	a_target.draw(m_selectionRect);	
}


/*
NAME
	void Editor::Render(sf::RenderTarget* a_target)

SYNOPSIS
	sf::RenderTarget* a_target	- The current window to draw to.

DESCRIPTION
	This function will draw onto the window features of the editor mode such as
	buttons and anything else that might be required.

AUTHOR
	Austin Rafuls

DATE
	8:42pm 8/9/2019
*/
void Editor::Render(sf::RenderTarget* a_target)
{
	if (!a_target)
	{
		a_target = m_window;
	}

	// Draw the world
	m_worldMap->Render(*a_target);

	// Draw the GUI
	RenderGUI(*a_target);

	// Draw pause menu
	if (m_pause)
	{
		m_pauseMenu->Render(*a_target);
	}

	// DEBUG -- REMOVE LATER
	sf::Text mt;
	mt.setPosition(m_mousePosCam.x - 2.f, m_mousePosCam.y - 15.f);
	mt.setFont(m_font);
	mt.setCharacterSize(12);
	std::stringstream ss;
	ss << m_mousePosCam.x << " " << m_mousePosCam.y;
	mt.setString(ss.str());
	a_target->draw(mt);
}


/*
NAME
	void Editor::UpdateKeys(const float & a_dt)

SYNOPSIS
	const float & a_dt	- Deltatime

DESCRIPTION
	This function will check for keys being pressed and execute their 
	functionality.

AUTHOR
	Austin Rafuls

DATE
	2:32pm 8/9/2019
*/
void Editor::UpdateKeys(const float & a_dt)
{
	// Quit Key
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybindings.at("CLOSE"))) && GetInputTimer())
	{
		if (m_pause)
		{
			Unpause();
		}
		else
		{
			Pause();
		}
	}
}


/*
NAME
	void Editor::UpdateEditorKeys()

SYNOPSIS
	const float & a_dt	- Deltatime

DESCRIPTION
	This function will check for keys being pressed while within the editor
	game mode.

AUTHOR
	Austin Rafuls

DATE
	10:06pm 8/9/2019
*/
void Editor::UpdateEditorKeys(const float & a_dt)
{
	// Add Tile to World
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && GetInputTimer())
	{
		m_worldMap->AddTile(m_mousePosGrd.x, m_mousePosGrd.y, 0);
	}
}
