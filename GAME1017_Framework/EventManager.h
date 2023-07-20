#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__
#include <SDL.h>

class EventManager
{
public: // Public methods.
	static void Init();
	static void HandleEvents();
	static bool KeyHeld(const SDL_Scancode key);
	static bool KeyPressed(const SDL_Scancode key);
	static bool KeyReleased(const SDL_Scancode key);
	static int LastKeyDown();
	static int LastKeyUp();
	static bool MouseHeld(const int btn);
	static bool MousePressed(const int btn);
	static bool MouseReleased(const int btn);
	static SDL_Point& GetMousePos();
	static bool ControllerButtonHeld(const int btn);
	static bool ControllerButtonPressed(const int btn);
	static bool ControllerButtonReleased(const int btn);
	static double ControllerAxis(const int axis);
	static int ControllerAxisRaw(const int axis);
	static void SetCursor(const SDL_SystemCursor& cursor);
	static void Quit();

private: // Private properties.
	// Keyboard state containers.
	static const Uint8* s_keysCurr;
	static Uint8* s_keysLast;
	static int s_numKeys;
	static int s_lastKeyDown;
	static int s_lastKeyUp;
	// Mouse state containers.
	static SDL_Point s_mousePos;
	static Uint32 s_mouseCurr;
	static Uint32 s_mouseLast;
	static SDL_Cursor* s_cursor;
	// Joystick properties.
	static SDL_GameController* s_gameController;
	static bool s_controllerButtonsCurr[15];
	static bool s_controllerButtonsLast[15];
	static void SetControllerButtons(bool* btns);
	static void CopyControllerButtons(bool* to, bool* from);
	EventManager() = default;	
};

typedef EventManager EVMA;

#endif