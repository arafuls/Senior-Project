#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "GUI.h"
#include "WorldMap.h"

class Editor :
	public State
{
private:
	WorldMap* m_worldMap;
	PauseMenu * m_pauseMenu;
	std::map<std::string, gui::Button*> m_buttons;
	gui::TextureMenu* m_textureMenu;

	sf::Font m_font;
	sf::RectangleShape m_selectionRect;
	sf::IntRect m_textureRect;
	sf::RectangleShape m_bar;

	void InitSettings();
	void InitFonts();
	void InitKeybindings();
	void InitGUI();
	void InitPauseMenu();
	void InitWorldMap();

public:
	Editor(StateDataContainer * a_stateData);
	virtual ~Editor();

	void Update(const float& a_dt);
	void UpdateGUI(const float & a_dt);
	void UpdatePauseGUI();
	void UpdateKeys(const float& a_dt);
	void UpdateEditorKeys(const float& a_dt);
	void RenderGUI(sf::RenderTarget & a_target);
	void Render(sf::RenderTarget* a_target = NULL);
};

