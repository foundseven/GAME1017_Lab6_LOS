#include "EventManager.h"
#include "Engine.h"
#include <cstring>
#include <iostream>

void EventManager::Init()
{
	s_keysCurr = SDL_GetKeyboardState(&s_numKeys);
	s_keysLast = new Uint8[s_numKeys];
	std::memcpy(s_keysLast, s_keysCurr, s_numKeys);
	s_mouseCurr = SDL_GetMouseState(&s_mousePos.x, &s_mousePos.y);
	s_mouseLast = s_mouseCurr;
	SetControllerButtons(s_controllerButtonsCurr);
	CopyControllerButtons(s_controllerButtonsLast, s_controllerButtonsCurr);
	//Check for joysticks
	if (SDL_NumJoysticks() < 1)
	{
		std::cout << "Warning: No joysticks connected!" << std::endl;
	}
	else
	{
		//Load joystick
		std::cout << "Joystick/controller connected!" << std::endl;
		s_gameController = SDL_GameControllerOpen(0);
		if (s_gameController == nullptr)
		{
			std::cout << "Warning: Unable to open game controller!" << std::endl;
		}
	}
	std::cout << "EventManager init success!" << std::endl;
}

void EventManager::HandleEvents()
{
	SDL_Event event;
	
	std::memcpy(s_keysLast, s_keysCurr, s_numKeys);
	s_mouseLast = s_mouseCurr;
	CopyControllerButtons(s_controllerButtonsLast, s_controllerButtonsCurr);
	s_lastKeyDown = s_lastKeyUp = -1;

	while (SDL_PollEvent(&event)) // Pump events invoked.
	{
		switch (event.type) // Parse some global events.
		{
			case SDL_QUIT: // User pressed window's 'x' button.
				Engine::Instance().Running() = false;
				break;
			case SDL_KEYDOWN:
				s_lastKeyDown = event.key.keysym.sym;
				break;
			case SDL_KEYUP:
				s_lastKeyUp = event.key.keysym.sym;
				if (event.key.keysym.sym == SDLK_ESCAPE)
					Engine::Instance().Running() = false;
				break;
		}
	}
	s_keysCurr = SDL_GetKeyboardState(&s_numKeys);
	s_mouseCurr = SDL_GetMouseState(&s_mousePos.x, &s_mousePos.y);
	SetControllerButtons(s_controllerButtonsCurr);
}

bool EventManager::KeyHeld(const SDL_Scancode key)
{
	if (s_keysCurr != nullptr)
	{
		if (s_keysCurr[key] == 1)
			return true;
		else
			return false;
	}
	return false;
}

bool EventManager::KeyPressed(const SDL_Scancode key)
{
	return (s_keysCurr[key] > s_keysLast[key]);
}

bool EventManager::KeyReleased(const SDL_Scancode key)
{
	return (s_keysCurr[key] < s_keysLast[key]);
}

int EventManager::LastKeyDown()
{
	return s_lastKeyDown;
}

int EventManager::LastKeyUp()
{
	return s_lastKeyUp;
}

bool EventManager::MouseHeld(const int btn)
{
	if (btn >= 1 && btn <= 3)
		return (s_mouseCurr & SDL_BUTTON(btn));
	else
		return false;
}

bool EventManager::MousePressed(const int btn)
{
	return ((s_mouseCurr & SDL_BUTTON(btn)) > (s_mouseLast & SDL_BUTTON(btn)));
}

bool EventManager::MouseReleased(const int btn)
{
	return ((s_mouseCurr & SDL_BUTTON(btn)) < (s_mouseLast & SDL_BUTTON(btn)));
}

SDL_Point& EventManager::GetMousePos()
{
	return s_mousePos;
}

bool EventManager::ControllerButtonHeld(const int btn)
{
	return SDL_GameControllerGetButton(s_gameController, static_cast<SDL_GameControllerButton>(btn));
}

bool EventManager::ControllerButtonPressed(const int btn)
{
	return (s_controllerButtonsCurr[btn] > s_controllerButtonsLast[btn]);
}

bool EventManager::ControllerButtonReleased(const int btn)
{
	return (s_controllerButtonsCurr[btn] < s_controllerButtonsLast[btn]);
}

double EventManager::ControllerAxis(const int axis)
{
	const int kDeadZone = 4000;
	double axisPerc = 0;
	switch (axis)
	{
		case 0:
		{
			int xAxis = SDL_GameControllerGetAxis(s_gameController, SDL_CONTROLLER_AXIS_LEFTX);
			if (xAxis < -kDeadZone)
				axisPerc = -(abs(xAxis) / 32768.0);
			else if (xAxis > kDeadZone)
				axisPerc = xAxis / 32767.0;
			else
				axisPerc = 0;
			break;
		}
		case 1:
		{
			int yAxis = SDL_GameControllerGetAxis(s_gameController, SDL_CONTROLLER_AXIS_LEFTY);
			if (yAxis < -kDeadZone)
				axisPerc = -(abs(yAxis) / 32768.0);
			else if (yAxis > kDeadZone)
				axisPerc = yAxis / 32767.0;
			else
				axisPerc = 0;
			break;
		}
	}
	return axisPerc;
}

int EventManager::ControllerAxisRaw(const int axis)
{
	const int kDeadZone = 4000;
	int axisRaw = 0;
	switch (axis)
	{
		case 0:
		{
			int xAxis = SDL_GameControllerGetAxis(s_gameController, SDL_CONTROLLER_AXIS_LEFTX);
			if (xAxis < -kDeadZone)
				axisRaw = -1;
			else if (xAxis > kDeadZone)
				axisRaw = 1;
			else
				axisRaw = 0;
			break;
		}
		case 1:
		{
			int yAxis = SDL_GameControllerGetAxis(s_gameController, SDL_CONTROLLER_AXIS_LEFTY);
			if (yAxis < -kDeadZone)
				axisRaw = -1;
			else if (yAxis > kDeadZone)
				axisRaw = 1;
			else
				axisRaw = 0;
			break;
		}
	}
	return axisRaw;
}

void EventManager::SetCursor(const SDL_SystemCursor& cursor)
{
	SDL_FreeCursor(s_cursor);
	s_cursor = SDL_CreateSystemCursor(cursor);
	SDL_SetCursor(s_cursor);
}

void EventManager::Quit()
{
	delete s_keysLast;
	SDL_FreeCursor(s_cursor);
	SDL_GameControllerClose(s_gameController);
	s_gameController = nullptr;
}

void EventManager::SetControllerButtons(bool* btns)
{
	for (int i = 0; i < 15; i++)
		btns[i] = SDL_GameControllerGetButton(s_gameController, static_cast<SDL_GameControllerButton>(i));
}

void EventManager::CopyControllerButtons(bool* to, bool* from)
{
	for (int i = 0; i < 15; i++)
		to[i] = from[i];
}

const Uint8* EventManager::s_keysCurr = nullptr;
Uint8* EventManager::s_keysLast;
int EventManager::s_numKeys;

int EventManager::s_lastKeyDown;
int EventManager::s_lastKeyUp;
SDL_Point EventManager::s_mousePos = { 0,0 };
Uint32 EventManager::s_mouseCurr;
Uint32 EventManager::s_mouseLast;

SDL_Cursor* EventManager::s_cursor;

SDL_GameController* EventManager::s_gameController = nullptr;
bool EventManager::s_controllerButtonsCurr[15] = { 0 };
bool EventManager::s_controllerButtonsLast[15] = { 0 };