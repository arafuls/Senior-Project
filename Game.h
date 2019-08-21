#pragma once
#include "MainMenuState.h"

class Game
{
private:
	// Window
	GfxContainer m_gfxSet;
	sf::RenderWindow* m_window;
	sf::Event m_event;

	// Clock
	sf::Clock m_dtClock;
	float m_dt;

	// Core
	std::stack<State*> m_states;	// Organizing active states in a stack
	std::map<std::string, int> m_suppKeys;
	StateDataContainer m_stateData;
	float m_worldGridSize;

	void InitSettings();
	void InitGFX();
	void InitWindow();
	void InitInput();
	void InitStates();
	void InitStateData();

public:
	Game();
	virtual ~Game();

	void UpdateDT();
	void UpdateSFMLEvents();
	void Update();
	void Render();
	void Run();
	void Quit();

};