#include "stdafx.h"
#include "State.h"


State::State(StateDataContainer * a_stateDataContainer)
{
	// Data Container Transfer
	m_stateData = a_stateDataContainer;
	m_window = a_stateDataContainer->m_window;
	m_suppKeys = a_stateDataContainer->m_suppKeys;
	m_states = a_stateDataContainer->m_states;
	m_worldGridSize = a_stateDataContainer->m_worldGridSize;

	// Default
	m_inputTimer = 0.f;
	m_inputTimerCap = 10.f;
	m_close = false;
	m_pause = false;
}


State::~State()
{
}


/*
NAME
	void State::GetExitRequest()

DESCRIPTION
	This function will return the current exit request status.

AUTHOR
	Austin Rafuls

DATE
	11:50am 7/16/2019
*/
const bool & State::GetExitRequest() const
{
	return m_close;
}


/*
NAME
	void State::GetInputTimer()

DESCRIPTION
	This is a simple accessor that will determine if a button press will be
	recognized depending on the input timers.

RETURNS
	Returns a boolean representing if the user's input will be acknowledged.

AUTHOR
	Austin Rafuls

DATE
	11:56am 8/8/2019
*/
const bool State::GetInputTimer()
{
	if (m_inputTimer >= m_inputTimerCap)
	{
		m_inputTimer = 0.f;
		return true;
	}
	return false;
}


/*
NAME
	void State::UpdateInputTimer()

SYNOPSIS
	const float a_dt	- Delta time

DESCRIPTION
	This function will update the input timer over time to prevent every input
	being recognized for every frame.

AUTHOR
	Austin Rafuls

DATE
	12:07pm 8/8/2019
*/
void State::UpdateInputTimer(const float & a_dt)
{
	if (m_inputTimer < m_inputTimerCap)
	{
		m_inputTimer += 45.f * a_dt;
	}
}


/*
NAME
	void State::UpdateMousePos()

DESCRIPTION
	This function will update the current mouse positions for the screen, 
	window, camera view, and grid view.

AUTHOR
	Austin Rafuls

DATE
	9:27pm 8/9/2019
*/
void State::UpdateMousePos()
{
	m_mousePosScr = sf::Mouse::getPosition();
	m_mousePosWin = sf::Mouse::getPosition(* m_window);
	m_mousePosCam = m_window->mapPixelToCoords(sf::Mouse::getPosition(* m_window));
	m_mousePosGrd = 
		sf::Vector2u(
			static_cast<unsigned int>(m_mousePosCam.x) / static_cast<unsigned int>(m_worldGridSize),
			static_cast<unsigned int>(m_mousePosCam.y) / static_cast<unsigned int>(m_worldGridSize)
		);
}


/*
NAME
	void State::EndState()

DESCRIPTION
	This function will update m_close to let the state know that is being
	requested to close.

AUTHOR
	Austin Rafuls

DATE
	8:24pm 8/1/2019
*/
void State::EndState()
{
	m_close = true;
}


/*
NAME
	void State::Pause()

DESCRIPTION
	Simple setter function to update m_pause to be true.

AUTHOR
	Austin Rafuls

DATE
	2:54pm 8/7/2019
*/
void State::Pause()
{
	m_pause = true;
}


/*
NAME
	void State::Unpause()

DESCRIPTION
	Simple setter function to update m_pause to be false.

AUTHOR
	Austin Rafuls

DATE
	2:54pm 8/7/2019
*/
void State::Unpause()
{
	m_pause = false;
}



StateDataContainer::StateDataContainer()
{
}