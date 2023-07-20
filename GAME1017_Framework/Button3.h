#ifndef __BUTTON3_H__
#define __BUTTON3_H__
#include <string>
#include "SDL.h"
#include "GameObject.h"

class Button3 : public Sprite
{
public:
	void Update();
	void Render();

protected:
	std::string m_key;
	enum BtnState { STATE_UP, STATE_OVER, STATE_DOWN } m_state; // enum defined locally.
	virtual void Execute() = 0; // Button3 is an abstract base class.
	Button3(SDL_Rect src, SDL_FRect dst, const char* key);
};

class PlayButton : public Button3
{
private:
	void Execute();
public:
	PlayButton(SDL_Rect src, SDL_FRect dst, const char* key);
};

#endif

