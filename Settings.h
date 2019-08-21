#pragma once
#include "State.h"
#include "GUI.h"

class Settings :
	public State
{
private:
	sf::Texture m_bgtexture;
	sf::RectangleShape m_bg;
	sf::Font m_font;
	std::map<std::string, gui::Button*> m_buttons;
	std::map<std::string, gui::DropDownList*> m_dropdownlists;
	sf::Text m_options;
	std::vector<sf::VideoMode> m_videoModes;

	void InitSettings();
	void InitFonts();
	void InitKeybindings();
	void InitGUI();
	void InitBG();

public:
	Settings(StateDataContainer * a_stateData);
	virtual ~Settings();

	void UpdateGUI(const float& a_dt);
	void Update(const float& a_dt);
	void RenderGUI(sf::RenderTarget & a_target);
	void Render(sf::RenderTarget* a_target = NULL);
	void UpdateKeys(const float& a_dt);
};

