#pragma once

class GfxContainer
{
private:
	std::string m_windowTitle;
	sf::VideoMode m_resolution;
	std::vector<sf::VideoMode> m_videoModes;
	sf::ContextSettings m_windowSettings;
	unsigned int m_fpsCap;
	bool m_vsyncEnabled;
	bool m_fullscreen;

public:

	GfxContainer();
	virtual ~GfxContainer();

	void SaveToFile(const std::string a_filePath);
	void LoadFromFile(const std::string a_filePath);

	bool GetFullscreen();
	sf::VideoMode GetVideoMode();
	std::string GetWindowTitle();
	sf::ContextSettings GetContextSettings();
	unsigned int GetFPSCap();
	bool GetVSyncEnabled();

	void SetFullscreen(const bool a_fullscreen);
	void SetResolution(const sf::VideoMode a_resolution);
	void SetWindowTitle(const std::string a_windowTitle);
	void SetContextSettings(const sf::ContextSettings a_windowSettings);
	void SetFPSCap(unsigned int a_fpsCap);
	void SetVSyncEnabled(bool a_vsyncEnabled);

};

