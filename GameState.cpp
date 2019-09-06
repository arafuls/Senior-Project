#include "stdafx.h"
#include "GameState.h"


/*
NAME
	void GameState::InitKeybindings()

DESCRIPTION
	This function will Initialize keybindings allowed for the gamestate 
	instance.

AUTHOR
	Austin Rafuls

DATE
	2:53pm 8/2/2019
*/
void GameState::InitKeybindings()
{
	// NOTE: Map removes duplicates for you, no need to check.
	std::ifstream keycfg("Config/gamestate_binds.ini");
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
	void GameState::InitPauseMenu()

DESCRIPTION
	This function will initialize the pause menu screen using saved settings
	from the GameState.

AUTHOR
	Austin Rafuls

DATE
	4:20pm 8/7/2019
*/
void GameState::InitPauseMenu()
{
	m_pauseMenu = new PauseMenu(*m_window, m_font);
	m_pauseMenu->AddButton("EXIT_GAME", "Main Menu", 500.f);
}


/*
NAME
	void GameState::InitTextures()

DESCRIPTION
	This function will Initialize the textures upon the the game's 
	instantiation. This allows all entities within the game to be
	assign a texture stored in the texture map.

AUTHOR
	Austin Rafuls

DATE
	2:58pm 8/2/2019
*/
void GameState::InitTextures()
{
	// Texture Sheet
	//if (!m_textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Sprites/IDLE.png"))
	if (!m_textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Sprites/test3.png"))
	{
		throw("Error: Could not load player sprite texture!");
	}
}


/*
NAME
	void GameState::InitPlayer()

DESCRIPTION
	This function will Initialize the player entity with a given texture and
	specific starting location through (x,y) coordinates.

AUTHOR
	Austin Rafuls

DATE
	3:01pm 8/2/2019
*/
void GameState::InitPlayer()
{
	m_player = new Player(m_textures["PLAYER_IDLE"], 0, 0);
}


/*
NAME
	void GameState::InitFont()

DESCRIPTION
	This function will initialize the desired font for the game and throw an
	exception if it could not be loaded.

AUTHOR
	Austin Rafuls

DATE
	4:15pm 8/7/2019
*/
void GameState::InitFont()
{
	if (!m_font.loadFromFile("Fonts/BebasNeue-Regular.ttf"))
	{
		throw("Error: Could not load font BebasNeue-Regular.ttf");
	}
}


/*
NAME
	void GameState::InitWorldMap()

DESCRIPTION
	This function will initialize and create the world map with all its tiles.

AUTHOR
	Austin Rafuls

DATE
	11:05pm 9/2/2019
*/
void GameState::InitWorldMap()
{
	m_worldMap = new WorldMap(
		m_stateData->m_worldGridSize, 
		10, 10, 
		"Resources/Images/World/textures1.png"
	);
	
	// Load world if there is a previous save
	if (!m_worldMap->LoadWorldMap("Test-Save.slmp"))
	{
		std::cout << "WARNING: Couldn't find saved world to load!" << std::endl;
	}
}


GameState::GameState(StateDataContainer * a_stateData)
	: State(a_stateData)
{
	InitKeybindings();
	InitFont();
	InitPauseMenu();
	InitTextures();
	InitPlayer();
	InitWorldMap();
}


GameState::~GameState()
{
	delete m_player;
	delete m_pauseMenu;
	delete m_worldMap;
}


/*
NAME
	void GameState::Update()

SYNOPSIS
	const float& a_dt	- Deltatime

DESCRIPTION
	This function will constantly update the location of the mouse, what keys
	are being pressed, and the location of moveable entity's.

AUTHOR
	Austin Rafuls

DATE
	12:00pm 8/8/2019
*/
void GameState::Update(const float& a_dt)
{
	// Always being updated
	UpdateInputTimer(a_dt);
	UpdateKeys(a_dt);
	UpdateMousePos();

	// Only update if not paused
	if (m_pause == false)
	{
		UpdateUserInput(a_dt);
		m_player->Update(a_dt);
	}
	// Only update if paused
	else
	{
		m_pauseMenu->Update(m_mousePosCam);
		UpdatePauseGUI();
	}
}


/*
NAME
	void GameState::Render(sf::RenderTarget* a_target)

SYNOPSIS
	sf::RenderTarget* a_target	- The current window to draw to.

DESCRIPTION
	This function will draw onto the window features of the main menu such as
	the background, button, and anything else that might be required.

AUTHOR
	Austin Rafuls

DATE
	12:55pm 8/9/2019
*/
void GameState::Render(sf::RenderTarget * a_target)
{
	if (!a_target)
	{
		a_target = m_window;
	}

	// Render the world textures
	m_worldMap->Render(*a_target);

	m_player->Render(* m_window);

	// Render pause menu
	if (m_pause == true)
	{
		m_pauseMenu->Render(*a_target);
	}
}


/*
NAME
	void GameState::UpdateUserInput(const float & a_dt)

SYNOPSIS
	const float& a_dt	- Deltatime

DESCRIPTION
	This function will check for an exit request by the user as well as any
	movement requests and handle them accordingly.

AUTHOR
	Austin Rafuls

DATE
	12:03pm 8/8/2019
*/
void GameState::UpdateUserInput(const float & a_dt)
{
	// Movement Keys
	if (sf::Keyboard::isKeyPressed
		(sf::Keyboard::Key(m_keybindings.at("MOVE_UP")))) 
	{ 
		m_player->Move(a_dt, 0.f, -1.f); 
	}

	if (sf::Keyboard::isKeyPressed
		(sf::Keyboard::Key(m_keybindings.at("MOVE_LEFT"))))
	{
		m_player->Move(a_dt, -1.f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed
		(sf::Keyboard::Key(m_keybindings.at("MOVE_DOWN"))))
	{ 
		m_player->Move(a_dt, 0.f, 1.f);
	}

	if (sf::Keyboard::isKeyPressed
		(sf::Keyboard::Key(m_keybindings.at("MOVE_RIGHT"))))
	{ 
		m_player->Move(a_dt, 1.f, 0.f);
	}
}


/*
NAME
	void GameState::UpdateKeys()

SYNOPSIS
	const float& a_dt	- Deltatime

DESCRIPTION
	This function will check to see the user is trying to pause the game and
	handle the functionality.

AUTHOR
	Austin Rafuls

DATE
	12:04pm 8/8/2019
*/
void GameState::UpdateKeys(const float & a_dt)
{
	// Pause Menu Key during gameplay
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybindings.at("CLOSE"))) && GetInputTimer())
	{
		if (m_pause == false)
		{
			Pause();
		}
		else
		{
			Unpause();
		}
		//EndState();
	}
}


/*
NAME
	void GameState::UpdatePauseGUI()

DESCRIPTION
	This function will check to see the user is interacting with the buttons
	within the pause menu and handle their functionality.

AUTHOR
	Austin Rafuls

DATE
	12:02pm 8/8/2019
*/
void GameState::UpdatePauseGUI()
{
	if (m_pauseMenu->IsPressed("EXIT_GAME"))
	{
		EndState();
	}
}
