#include "stdafx.h"
#include "Editor.h"


/*
NAME
	void Editor::InitSettings()

DESCRIPTION
	This function will initialize setting for the game editor upon 
	instantiation.

AUTHOR
	Austin Rafuls

DATE
	4:46pm 8/23/2019
*/
void Editor::InitSettings()
{
	// Texture Rectangle to navigate texture sheet for the world.
	m_textureRect = 
		sf::IntRect(
			0, 
			0, 
			static_cast<int>(m_stateData->m_worldGridSize), 
			static_cast<int>(m_stateData->m_worldGridSize)
		);
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
	2:44pm 8/23/2019
*/
void Editor::InitGUI()
{
	//m_bar.setPosition
	m_bar.setSize(sf::Vector2f(80.f, static_cast<float>(m_stateData->m_gfxSettings->GetVideoMode().height)));
	m_bar.setFillColor(sf::Color(50, 50, 50, 100));
	m_bar.setOutlineColor(sf::Color(200, 200, 200, 150));
	m_bar.setOutlineThickness(1.f);

	m_selectionRect.setSize(sf::Vector2f(m_stateData->m_worldGridSize, m_stateData->m_worldGridSize));
	//m_selectionRect.setFillColor(sf::Color::Transparent);
	m_selectionRect.setFillColor(sf::Color(255, 255, 255, 150));
	m_selectionRect.setOutlineThickness(1.f);
	m_selectionRect.setOutlineColor(sf::Color::Yellow);
	m_selectionRect.setTexture(m_worldMap->GetTileTextures());
	m_selectionRect.setTextureRect(m_textureRect);

	// TODO: Make this not hardcoded.
	m_textureMenu = new gui::TextureMenu(m_worldMap->GetTileTextures(), 100.f, 10.f, 900.f, 100.f, m_stateData->m_worldGridSize, m_font, "TOGGLE");
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
	7:12pm 8/28/2019
*/
void Editor::InitPauseMenu()
{
	m_pauseMenu = new PauseMenu(*m_window, m_font);

	m_pauseMenu->AddButton("LOAD_GAME", "Load World", 350.f);
	m_pauseMenu->AddButton("SAVE_GAME", "Save World", 425.f);
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
	8:17pm 8/23/2019
*/
void Editor::InitWorldMap()
{
	m_worldMap = new WorldMap(
		m_stateData->m_worldGridSize, 
		10, 10, 
		"Resources/Images/World/textures1.png");
}


Editor::Editor(StateDataContainer * a_stateData)
	: State(a_stateData)
{
	InitSettings();
	InitFonts();
	InitKeybindings();
	InitPauseMenu();
	InitWorldMap();
	InitGUI();
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
	delete m_textureMenu;
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
	7:12pm 8/28/2019
*/
void Editor::UpdatePauseGUI()
{
	if (m_pauseMenu->IsPressed("EXIT_GAME"))
	{
		EndState();
	}

	if (m_pauseMenu->IsPressed("SAVE_GAME"))
	{
		m_worldMap->SaveWorldMap("Test-Save.slmp");
	}

	if (m_pauseMenu->IsPressed("LOAD_GAME"))
	{
		m_worldMap->LoadWorldMap("Test-Save.slmp");
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
	5:49pm 8/23/2019
*/
void Editor::UpdateGUI(const float & a_dt)
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

	// Update texture selection menu
	m_textureMenu->Update(m_mousePosWin, a_dt);

	// Update texture selection rect _IF_ active
	if (m_textureMenu->IsActive())
	{
		m_selectionRect.setTextureRect(m_textureRect);
		m_selectionRect.setPosition(m_mousePosGrd.x * m_stateData->m_worldGridSize, m_mousePosGrd.y * m_stateData->m_worldGridSize);
	}
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
	5:49pm 8/23/2019
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
		UpdateGUI(a_dt);
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
	6:32pm 8/23/2019
*/
void Editor::RenderGUI(sf::RenderTarget & a_target)
{
	// Draw buttons
	for (auto &button : m_buttons)
	{
		button.second->Render(a_target);
	}

	// Draw texture selection menu
	m_textureMenu->Render(a_target);

	// If TextureMenu is inactive
	if (!m_textureMenu->IsActive() && !m_bar.getGlobalBounds().contains(sf::Vector2f(m_mousePosWin)))
	{	
		// Draw selection rectangle
		a_target.draw(m_selectionRect);
	}

	// Draw sidebar
	a_target.draw(m_bar);
}


/*
NAME
	void Editor::Render()

SYNOPSIS
	sf::RenderTarget* a_target	- The current window to draw to.

DESCRIPTION
	This function will draw onto the window features of the editor mode such as
	buttons and anything else that might be required.

AUTHOR
	Austin Rafuls

DATE
	2:26pm 8/23/2019
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
	//sf::Text mt;
	//mt.setPosition(m_mousePosCam.x - 2.f, m_mousePosCam.y - 15.f);
	//mt.setFont(m_font);
	//mt.setCharacterSize(12);
	//std::stringstream ss;
	//ss << m_mousePosCam.x << " " << m_mousePosCam.y;
	//mt.setString(ss.str());
	//a_target->draw(mt);
}


/*
NAME
	void Editor::UpdateKeys()

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
	6:25pm 8/23/2019
*/
void Editor::UpdateEditorKeys(const float & a_dt)
{
	// Adding/Removing Tiles to World
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && GetInputTimer())
	{
		// If mouse is not within side bar
		if (!m_bar.getGlobalBounds().contains(sf::Vector2f(m_mousePosWin)))
		{
			if (!m_textureMenu->IsActive())
			{
				// Add tile
				m_worldMap->AddTile(m_mousePosGrd.x, m_mousePosGrd.y, 0, m_textureRect);
			}
			else
			{
				// Select tile
				m_textureRect = m_textureMenu->GetTextureRect();
			}
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && GetInputTimer())
	{
		// If mouse is not within side bar
		if (!m_bar.getGlobalBounds().contains(sf::Vector2f(m_mousePosWin)))
		{
			if (!m_textureMenu->IsActive())
			{
				// Remove tile
				m_worldMap->RemoveTile(m_mousePosGrd.x, m_mousePosGrd.y, 0);
			}
		}
	}


}
