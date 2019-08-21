#include "stdafx.h"
#include "GfxContainer.h"

GfxContainer::GfxContainer()
{
	m_windowTitle = "DEFAULT";
	m_resolution = sf::VideoMode::getDesktopMode();
	m_videoModes = sf::VideoMode::getFullscreenModes();
	m_windowSettings.antialiasingLevel = 0;
	m_fpsCap = 144;
	m_vsyncEnabled = false;
	m_fullscreen = false;
}


GfxContainer::~GfxContainer()
{
}


/*
NAME
	void GfxContainer::SaveToFile()

SYNOPSIS
	const std::string a_filePath	- File path to save settings into.

DESCRIPTION
	This function will save the current graphical engine settings to the
	graphics config file.

AUTHOR
	Austin Rafuls

DATE
	1:25pm 8/9/2019
*/
void GfxContainer::SaveToFile(const std::string a_filePath)
{
	// Configuration file
	std::ofstream cfg(a_filePath);

	// Write settings to config file
	if (cfg.is_open())
	{
		cfg << m_windowTitle;
		cfg << m_resolution.width << " " << m_resolution.height;
		cfg << m_fpsCap;
		cfg << m_windowSettings.antialiasingLevel;
		cfg << m_vsyncEnabled;
		cfg << m_fullscreen;
	}
	cfg.close();
}


/*
NAME
	void GfxContainer::LoadFromFile()

SYNOPSIS
	const std::string a_filePath	- File path to load settings from.

DESCRIPTION
	This function will load the current graphical engine settings from the
	graphics config file.

AUTHOR
	Austin Rafuls

DATE
	1:20pm 8/9/2019
*/
void GfxContainer::LoadFromFile(const std::string a_filePath)
{
	// Configuration file
	std::ifstream cfg(a_filePath);

	// Parse settings from config file
	if (cfg.is_open())
	{
		std::getline(cfg, m_windowTitle);
		cfg >> m_resolution.width >> m_resolution.height;
		cfg >> m_fpsCap;
		cfg >> m_windowSettings.antialiasingLevel;
		cfg >> m_vsyncEnabled;
		cfg >> m_fullscreen;
	}
	cfg.close();
}


/*
NAME
	bool GfxContainer::GetFullscreen()

DESCRIPTION
	Accessor to get the current fullscreen status.

RETURNS
	Returns a bool, true if fullscreen and false if windowed.

AUTHOR
	Austin Rafuls

DATE
	1:28pm 8/9/2019
*/
bool GfxContainer::GetFullscreen()
{
	return m_fullscreen;
}


/*
NAME
	sf::VideoMode GfxContainer::GetVideoMode()

DESCRIPTION
	Accessor to get the current video mode of the window.

RETURNS
	Returns the current sf::VideoMode setting that is saved.

AUTHOR
	Austin Rafuls

DATE
	1:29pm 8/9/2019
*/
sf::VideoMode GfxContainer::GetVideoMode()
{
	return m_resolution;
}


/*
NAME
	std::string GfxContainer::GetWindowTitle()

DESCRIPTION
	Accessor to get the current window title.

RETURNS
	Returns a std::string with the title for the game window.

AUTHOR
	Austin Rafuls

DATE
	1:32pm 8/9/2019
*/
std::string GfxContainer::GetWindowTitle()
{
	return m_windowTitle;
}


/*
NAME
	sf::ContextSettings GfxContainer::GetContextSettings()

DESCRIPTION
	Accessor to get the current window context settings.

RETURNS
	Returns a sf::ContextSettings of the current windows context settings.

AUTHOR
	Austin Rafuls

DATE
	1:33pm 8/9/2019
*/
sf::ContextSettings GfxContainer::GetContextSettings()
{
	return m_windowSettings;
}


/*
NAME
	unsigned int GfxContainer::GetFPSCap()

DESCRIPTION
	Accessor to get the current window frame per second upper limit.

RETURNS
	Returns an unsigned int representing the max frames per second.

AUTHOR
	Austin Rafuls

DATE
	1:36pm 8/9/2019
*/
unsigned int GfxContainer::GetFPSCap()
{
	return m_fpsCap;
}


/*
NAME
	bool GfxContainer::GetVSyncEnabled()

DESCRIPTION
	Accessor to see if vertical sync is enabled or not.

RETURNS
	Returns a bool, true if vsync is enabled and false if disabled.

AUTHOR
	Austin Rafuls

DATE
	1:37pm 8/9/2019
*/
bool GfxContainer::GetVSyncEnabled()
{
	return m_vsyncEnabled;
}


/*
NAME
	void GfxContainer::SetFullscreen()

SYNOPSIS
	const bool a_fullscreen	- The desired window mode

DESCRIPTION
	Setter function to override the current window mode

AUTHOR
	Austin Rafuls

DATE
	2:13pm 8/9/2019
*/
void GfxContainer::SetFullscreen(const bool a_fullscreen)
{
	m_fullscreen = a_fullscreen;
}


/*
NAME
	void GfxContainer::SetResolution()

SYNOPSIS
	const sf::VideoMode a_resolution	- The desired window resolution

DESCRIPTION
	Setter function to override the old window resolution with a new one.

AUTHOR
	Austin Rafuls

DATE
	2:04pm 8/9/2019
*/
void GfxContainer::SetResolution(const sf::VideoMode a_resolution)
{
	m_resolution = a_resolution;
}


/*
NAME
	void GfxContainer::SetWindowTitle()

SYNOPSIS
	const std::string a_windowTitle	- The desired window title

DESCRIPTION
	Setter function to override the current window title

AUTHOR
	Austin Rafuls

DATE
	2:14pm 8/9/2019
*/
void GfxContainer::SetWindowTitle(const std::string a_windowTitle)
{
	m_windowTitle = a_windowTitle;
}


/*
NAME
	void GfxContainer::SetContextSettings()

SYNOPSIS
	const sf::ContextSettings a_windowSettings	- The desired window context settings

DESCRIPTION
	Setter function to override the current window context settings

AUTHOR
	Austin Rafuls

DATE
	2:15pm 8/9/2019
*/
void GfxContainer::SetContextSettings(const sf::ContextSettings a_windowSettings)
{
	m_windowSettings = a_windowSettings;
}


/*
NAME
	void GfxContainer::SetFPSCap()

SYNOPSIS
	unsigned int a_fpsCap	- The desired upper limit for frames per second

DESCRIPTION
	Setter function to override the current window capacity for frames per second

AUTHOR
	Austin Rafuls

DATE
	2:15pm 8/9/2019
*/
void GfxContainer::SetFPSCap(unsigned int a_fpsCap)
{
	m_fpsCap = a_fpsCap;
}


/*
NAME
	void GfxContainer::SetVSyncEnabled()

SYNOPSIS
	bool a_vsyncEnabled	-	The desired vertical sync setting

DESCRIPTION
	Setter function to override the current window vertical sync setting.

AUTHOR
	Austin Rafuls

DATE
	2:16pm 8/9/2019
*/
void GfxContainer::SetVSyncEnabled(bool a_vsyncEnabled)
{
	m_vsyncEnabled = a_vsyncEnabled;
}
