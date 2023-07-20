#include "StateManager.h"
#include <iostream>

void StateManager::Update()
{
	if (s_stateChange == true)
		s_stateChange = false;
	if (!s_states.empty()) 
		s_states.back()->Update(); // s_states.back() represents the current state running.
}

void StateManager::Render()
{
	if (!s_states.empty())
		s_states.back()->Render();
}

// Used when there are 2 states in vector, i.e. Game and Pause.
void StateManager::PushState(State* state) // Going from Game to Pause.
{
	s_states.push_back(state); // pState now becomes current state.
	s_states.back()->Enter();
}

// Used when there are 2 states in vector, i.e. Game and Pause.
void StateManager::PopState() // Going from Pause back to Game.
{
	if (s_states.size() <= 1) return;
	s_stateChange = true;
	if (!s_states.empty())
	{
		s_states.back()->Exit(); // Cleans up current state.
		delete s_states.back(); // Deallocates current state.
		s_states.back() = nullptr; // Wrangle our dangle.
		s_states.pop_back(); // Removed nullptr to deallocated current state.
	}
	s_states.back()->Resume();
}

void StateManager::ChangeState(State* state)
{
	s_stateChange = true;
	if (!s_states.empty())
	{
		s_states.back()->Exit(); // Cleans up current state.
		delete s_states.back(); // Deallocates current state.
		s_states.back() = nullptr; // Wrangle our dangle.
		s_states.pop_back(); // Removed nullptr to deallocated current state.
	}
	s_states.push_back(state);
	s_states.back()->Enter();
}

void StateManager::Quit()
{
	while (!s_states.empty())
	{
		s_states.back()->Exit(); // Cleans up current state.
		delete s_states.back(); // Deallocates current state.
		s_states.back() = nullptr; // Wrangle our dangle.
		s_states.pop_back(); // Removed nullptr to deallocated current state.
	}
}

State* StateManager::CurrentState() { return s_states.back(); }
std::vector<State*>& StateManager::GetStates() { return s_states; }
const bool StateManager::StateChanging() { return s_stateChange; }

std::vector<State*> StateManager::s_states; // This now will be allocated memory. It now "exists".
bool StateManager::s_stateChange = false;