#pragma once
#include "GameState.h"
#include "Editor.h"
#include "GUI.h"
#include "Settings.h"

class MainMenuState :
	public State
{
private:
	sf::Texture m_bgtexture;
	sf::RectangleShape m_bg;
	sf::Font m_font;
	std::map<std::string, gui::Button*> m_buttons;

	void InitSettings();
	void InitFonts();
	void InitKeybindings();
	void InitGUI();
	void InitBG();

public:
	MainMenuState(StateDataContainer * a_stateData);
	virtual ~MainMenuState();

	void UpdateGUI();
	void Update(const float& a_dt);
	void RenderGUI(sf::RenderTarget & a_target);
	void Render(sf::RenderTarget* a_target = NULL);
	void UpdateKeys(const float& a_dt);
};

