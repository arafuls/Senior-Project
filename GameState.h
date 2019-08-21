#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "WorldMap.h"

class GameState :
	public State
{
private:
	Player* m_player;
	PauseMenu* m_pauseMenu;
	sf::Font m_font;
	WorldMap* m_worldMap;

	void InitKeybindings();
	void InitPauseMenu();
	void InitTextures();
	void InitPlayer();
	void InitFont();
	void InitWorldMap();

public:
	GameState(StateDataContainer * a_stateData);
	virtual ~GameState();

	void Update(const float & a_dt);
	void Render(sf::RenderTarget * a_target = NULL);
	void UpdateUserInput(const float & a_dt);
	void UpdateKeys(const float & a_dt);
	void UpdatePauseGUI();
};

