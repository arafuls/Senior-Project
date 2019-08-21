#include "stdafx.h"
#include "Settings.h"

// TODO: Documentation
void Settings::InitSettings()
{
	m_videoModes = sf::VideoMode::getFullscreenModes();
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
void Settings::InitFonts()
{
	if (!m_font.loadFromFile("Fonts/BebasNeue-Regular.ttf"))
		//if (!m_font.loadFromFile("Fonts/Black-Melody.otf"))
	{
		throw("Error: Could not load font BebasNeue-Regular.ttf");
	}
}


/*
NAME
	void Settings::InitKeybindings()

DESCRIPTION
	This function will Initialize the desired key bindings for the main menu
	game state by overwriting them from an ini file.

AUTHOR
	Austin Rafuls

DATE
	12:45pm 8/8/2019
*/
void Settings::InitKeybindings()
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
	void Settings::InitGUI()

DESCRIPTION
	This function will Initialize the Graphical User Interface for the main
	menu, specifically the interactable buttons.

AUTHOR
	Austin Rafuls

DATE
	5:50pm 8/8/2019
*/
void Settings::InitGUI()
{
	// Display Current Options
	m_options.setFont(m_font);
	m_options.setPosition(sf::Vector2f(40.f, 30.f));
	m_options.setCharacterSize(30);
	m_options.setFillColor(sf::Color(200, 200, 200, 200));
	m_options.setString("Resolution \n\nFullscreen \n\nV-Sync \n\nAA");

	/* * * * * Button Placement * * * * */
	m_buttons["EXIT_GAME"] = new gui::Button(
		80.f, 600.f, 150, 50,
		&m_font, 32, "Return",
		sf::Color::White, sf::Color::Yellow, sf::Color::Transparent,				// Text
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,		// Background
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);	// Outline

	m_buttons["SAVE_CHANGES"] = new gui::Button(
		280.f, 600.f, 150, 50,
		&m_font, 32, "Save",
		sf::Color::White, sf::Color::Yellow, sf::Color(20, 20, 20, 150),
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

	// Dropdownlist
	std::vector<std::string> videomodes_str;

	// Converting our videomodes to strings
	for (auto &resolution : m_videoModes)
	{
		videomodes_str.push_back(std::to_string(resolution.width) + " x " + std::to_string(resolution.height));
	}

	// Add them to dropdownlist items
	m_dropdownlists["RESOLUTION"] = new gui::DropDownList(200.f, 30.f, 150, 35, videomodes_str.data(), m_font, 0, videomodes_str.size());
}


/*
NAME
	void Settings::InitBG()

DESCRIPTION
	This function will Initialize the background image for the main menu.

AUTHOR
	Austin Rafuls

DATE
	12:45pm 8/8/2019
*/
void Settings::InitBG()
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


Settings::Settings(StateDataContainer * a_stateData)
	: State(a_stateData)
{
	InitSettings();
	InitFonts();
	InitKeybindings();
	InitGUI();
	InitBG();
}


Settings::~Settings()
{
	// Delete buttons
	auto button = m_buttons.begin();
	for (button = m_buttons.begin(); button != m_buttons.end(); button++)
	{
		delete button->second;
	}

	// Delete dropdownlist items
	auto item = m_dropdownlists.begin();
	for (item = m_dropdownlists.begin(); item != m_dropdownlists.end(); item++)
	{
		delete item->second;
	}
}


/*
NAME
	void Settings::UpdateGUI()

SYNOPSIS
	const float& a_dt	- Delta time

DESCRIPTION
	This function will update the GUI and handle their functionality.

AUTHOR
	Austin Rafuls

DATE
	8:23pm 8/9/2019
*/
void Settings::UpdateGUI(const float& a_dt)
{
	/* * * * UPDATE BUTTONS SECTION * * * */
	// Interacting with any button
	for (auto &button : m_buttons)
	{
		button.second->Update(m_mousePosCam);
	}

	// Main Menu button functionality
	if (m_buttons["EXIT_GAME"]->IsPressed())
	{
		EndState();
	}

	// Save button functionality
	if (m_buttons["SAVE_CHANGES"]->IsPressed())
	{
		// DEBUG -- REMOVE LATER

		// Save current resolution
		m_stateData->m_gfxSettings->SetResolution(
			m_videoModes[m_dropdownlists["RESOLUTION"]->GetActiveElementIdentifier()]);

		// Window Prompt to User
		m_window->create(
			m_stateData->m_gfxSettings->GetVideoMode(),
			m_stateData->m_gfxSettings->GetWindowTitle(), 
			sf::Style::Default
		);
	}

	/* * * * UPDATE DROPDOWNLIST SECTION * * * */
	// Interacting with dropdownlist items
	for (auto &item : m_dropdownlists)
	{
		item.second->Update(m_mousePosCam, a_dt);
	}

	// Dropdownlist item functionality

}


/*
NAME
	void Settings::Update()

SYNOPSIS
	const float& a_dt	- Deltatime

DESCRIPTION
	This function will constantly loop to update the main menu's gui and state
	status.

AUTHOR
	Austin Rafuls

DATE
	12:45pm 8/8/2019
*/
void Settings::Update(const float& a_dt)
{
	UpdateMousePos();
	UpdateKeys(a_dt);
	UpdateGUI(a_dt);
}


/*
NAME
	void Settings::RenderGUI()

DESCRIPTION
	This function will iterate through all buttons in the map and render them.

AUTHOR
	Austin Rafuls

DATE
	4:33pm 8/8/2019
*/
void Settings::RenderGUI(sf::RenderTarget & a_target)
{
	// Draw all buttons
	for (auto &button : m_buttons)
	{
		button.second->Render(a_target);
	}

	// Draw all dropdownlist items
	for (auto &item : m_dropdownlists)
	{
		item.second->Render(a_target);
	}
}


/*
NAME
	void Settings::Render()

SYNOPSIS
	sf::RenderTarget* a_target	- The current window to draw to.

DESCRIPTION
	This function will draw onto the window features of the main menu such as
	the background, button, and anything else that might be required.

AUTHOR
	Austin Rafuls

DATE
	6:03pm 8/8/2019
*/
void Settings::Render(sf::RenderTarget * a_target)
{
	if (!a_target)
	{
		a_target = m_window;
	}

	a_target->draw(m_bg);
	RenderGUI(*a_target);

	a_target->draw(m_options);
}


/*
NAME
	void Settings::UpdateKeys()

SYNOPSIS
	const float & a_dt	- Deltatime

DESCRIPTION
	This function will 

AUTHOR
	Austin Rafuls

DATE
	
*/
void Settings::UpdateKeys(const float & a_dt)
{

}