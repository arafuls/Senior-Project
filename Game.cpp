/* The bare bones of this class was taken from the SFML tutorial page and was
	broken down into functions.

	The code used can be found at the following URL near the bottom of the 
	page: https://www.sfml-dev.org/tutorials/2.5/start-vc.php				*/
#include "stdafx.h"
#include "Game.h"


/*
NAME
	void Game::InitSettings()

DESCRIPTION
	This function will Initialize the games application settings before
	launching as a safeguard.

AUTHOR
	Austin Rafuls

DATE
	7:03pm 8/9/2019
*/
void Game::InitSettings()
{
	m_window = NULL;
	//m_dt = 0.f;
	m_worldGridSize = 50.f;
}


/*
NAME
	void Game::InitSettings()

DESCRIPTION
	This function will initialize the games graphical settings prior to 
	launching.

AUTHOR
	Austin Rafuls

DATE
	1:11pm 8/9/2019
*/
void Game::InitGFX()
{
	m_gfxSet.LoadFromFile("Config/gfx.ini");
}


/*
NAME
	void Game::InitWindow()

DESCRIPTION
	This function will initialize the window to be used for 2D drawing with
	setting that are desireable for the game window such as fullscreen,
	height, width, max frames per second, and more.

AUTHOR
	Austin Rafuls

DATE
	1:39pm 8/9/2019
*/
void Game::InitWindow()
{
	if (m_gfxSet.GetFullscreen())
	{
		// Fullscreen window
		m_window = new sf::RenderWindow(
			m_gfxSet.GetVideoMode(),
			m_gfxSet.GetWindowTitle(),
			sf::Style::Fullscreen,
			m_gfxSet.GetContextSettings()
		);
	}
	else
	{
		// Bordered window with Titlebar and Close button only
		m_window = new sf::RenderWindow(
			m_gfxSet.GetVideoMode(),
			m_gfxSet.GetWindowTitle(),
			sf::Style::Titlebar | sf::Style::Close,
			m_gfxSet.GetContextSettings()
		);
	}
	
	// Other Settings
	m_window->setFramerateLimit(m_gfxSet.GetFPSCap());
	m_window->setVerticalSyncEnabled(m_gfxSet.GetVSyncEnabled());
}


/*
NAME
	void Game::InitInput()

DESCRIPTION
	This function will Initialize the input keys that are allowed to be used
	during each state's instantiation.

AUTHOR
	Austin Rafuls

DATE
	11:54am 7/30/2019
*/
void Game::InitInput()
{
	// NOTE: Map removes duplicates for you, no need to check.
	std::ifstream keycfg("Config/supported_keys.ini");
	if (keycfg.is_open())
	{
		std::string key = "";
		int keyvalue = 0;

		while (keycfg >> key >> keyvalue)
		{
			m_suppKeys[key] = keyvalue;
		}
	}
	keycfg.close();

	// DEBUG
	for (auto i : m_suppKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
}


/*
NAME
	void Game::InitStates()

DESCRIPTION
	This function will Initialize the game's current states by pushing the
	current active state onto the state stack.

AUTHOR
	Austin Rafuls

DATE
	7:13pm 8/9/2019
*/
void Game::InitStates()
{
	m_states.push(new MainMenuState(& m_stateData));
}


// TODO: Documentation completed 7:01pm 8/9/2019
void Game::InitStateData()
{
	m_stateData.m_window = m_window;
	m_stateData.m_gfxSettings = & this->m_gfxSet;
	m_stateData.m_suppKeys = & this->m_suppKeys;
	m_stateData.m_states = & this->m_states;
	m_stateData.m_worldGridSize = this->m_worldGridSize;
}


Game::Game()
{
	InitSettings();
	InitGFX();
	InitWindow();
	InitInput();
	InitStateData();
	InitStates();
}


Game::~Game() 
{
	delete m_window;

	while (!m_states.empty())
	{
		delete m_states.top();
		m_states.pop();
	}
}

/*
NAME
	void Game::UpdateDT()

DESCRIPTION
	Updates m_dt variable with the time in seconds it took to update and render
	a single frame.

AUTHOR
	Austin Rafuls

DATE
	9:39am 7/16/2019
*/
void Game::UpdateDT()
{
	m_dt = m_dtClock.restart().asSeconds();
	//system("cls");
	//std::cout << m_dt << std::endl;
}

/*
NAME
	void Game::UpdateSFMLEvents()

DESCRIPTION
	This function will constantly check if there is an event queued, if there
	is then it will process the event and move onto the next.

AUTHOR
	Austin Rafuls

DATE
	10:52am 7/16/2019
*/
void Game::UpdateSFMLEvents()
{
	// If there is an event queued, process it
	while (m_window->pollEvent(m_event))
	{
		// If the event was requested to be closed
		if (m_event.type == sf::Event::Closed) 
		{ 
			// Close it
			m_window->close(); 
		}
	}
}

/*
NAME
	void Game::Update()

DESCRIPTION
	This function will constantly be called during the games lifetime to
	update to most recently used game state by calling that respective
	state's update procedure.

AUTHOR
	Austin Rafuls

DATE
	11:11am 7/16/2019
*/
void Game::Update()
{
	// Check event queues
	UpdateSFMLEvents();

	// If there is an active state
	if (!m_states.empty())
	{
		// Update the most recent game state
		m_states.top()->Update(m_dt);

		// If state is requesting to be terminated
		if (m_states.top()->GetExitRequest())
		{
			// Serialization
			m_states.top()->EndState();

			// Delete the state and remove it from the stack
			delete m_states.top();
			m_states.pop();
		}
	}
	else
	{
		// Terminate application
		Quit();
		m_window->close();
	}
}

/*
NAME
	void Game::Render()

DESCRIPTION
	This function will constantly be called during the games lifetime to
	render to most recently used game state by calling that respective
	state's render procedure.

AUTHOR
	Austin Rafuls

DATE
	11:13am 7/16/2019
*/
void Game::Render()
{
	// Wipe the current window
	m_window->clear();

	// If there is an active state
	if (!m_states.empty())
	{
		// Render the most recent game state
		m_states.top()->Render(m_window);
	}

	// Display what has been rendered
	m_window->display();
}

/*
NAME
	void Game::Run()

DESCRIPTION
	This function will constantly run the game in a while loop while the game
	window is open.

AUTHOR
	Austin Rafuls

DATE
	10:51am 7/16/2019
*/
void Game::Run()
{
	while (m_window->isOpen())
	{
		UpdateDT();
		Update();
		Render();
	}
}


/*
NAME
	void Game::Quit()

DESCRIPTION
	This function will perform any last operations before closing the 
	application.

AUTHOR
	Austin Rafuls

DATE
	3:06am 7/30/2019
*/
void Game::Quit()
{
	//std::cout << "Terminating game. . .";
}