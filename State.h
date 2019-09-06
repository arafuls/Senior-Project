/* This controls the games current state. */
/* Only load in necessary textures for the game based on the state.
You don't need many resources for the main menu.*/
#pragma once
#include "Player.h"
#include "GfxContainer.h"

// Forward declaration so State class can be found
class State;


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/* The purpose of this class object is to transfer data in a more readable
	manner. Having several lines of parameters is very ugly and confusing. 
	
	Attributes do not need to be private because the StateDataContainer
	itself is to be a protected/private object in its governing body.		*/
class StateDataContainer
{
public:
	StateDataContainer();

	sf::RenderWindow* m_window;
	std::map<std::string, int>* m_suppKeys;
	std::stack<State*>* m_states;
	GfxContainer* m_gfxSettings;
	float m_worldGridSize;
};


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


class State
{
private:

protected:
	// Core
	float m_inputTimer;
	float m_inputTimerCap;

	StateDataContainer* m_stateData;
	std::stack<State*>* m_states;	// Univeral state stack for each state
	sf::RenderWindow* m_window;
	std::map<std::string, int>* m_suppKeys;
	std::map<std::string, int> m_keybindings;
	bool m_close;
	bool m_pause;

	float m_worldGridSize;

	// Mouse
	sf::Vector2i m_mousePosScr; // Screen View
	sf::Vector2i m_mousePosWin; // Window View
	sf::Vector2f m_mousePosCam;	// Camera View
	sf::Vector2u m_mousePosGrd;	// Grid View

	// Resources
	std::map<std::string, sf::Texture> m_textures;

	virtual void InitKeybindings() = 0;

public:
	State(StateDataContainer * a_stateDataContainer);
	virtual ~State();

	void EndState();
	void Pause();
	void Unpause();
	const bool& GetExitRequest() const;
	const bool GetInputTimer();

	virtual void UpdateInputTimer(const float & a_dt);
	virtual void UpdateMousePos();
	/* 
	Pure Virtual Functions Safeguard
		Assigning these to zero enforced all inherited objects to implement
		these functions in order to avoid crashing. 
	*/
	virtual void Update(const float& a_dt) = 0;
	virtual void UpdateKeys(const float& a_dt) = 0;
	virtual void Render(sf::RenderTarget* a_target = NULL) = 0;
};

