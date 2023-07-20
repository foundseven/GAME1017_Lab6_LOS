#ifndef __STATEMANAGER_H__
#define __STATEMANAGER_H__
#include "States.h"
#include <vector>

// We're going to make StateManager a "static class".
class StateManager // This is our finite state machine (FSM)
{
public:
	static void Update();
	static void Render();
	static void PushState(State* state);
	static void PopState();
	static void ChangeState(State* state);
	static void Quit();
	static State* CurrentState(); // Get for current state.
	static std::vector<State*>& GetStates(); // Getter for the s_states.
	static const bool StateChanging();

private:
	static std::vector<State*> s_states; // s_ is my convention for static properties.
	static bool s_stateChange;
	StateManager() = default;
};

typedef StateManager STMA;

#endif

