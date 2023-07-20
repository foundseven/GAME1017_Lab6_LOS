#include "Button3.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "TextureManager.h"
#include "StateManager.h"

Button3::Button3(SDL_Rect src, SDL_FRect dst, const char* key) :Sprite(src, dst), m_state(STATE_UP), m_key(key) {}

void Button3::Update()
{
	bool col = COMA::PointAABBCheck(EVMA::GetMousePos(), m_dst);
	switch (m_state)
	{
	case STATE_UP:
		if (col)
		{
			m_state = STATE_OVER;
			EVMA::SetCursor(SDL_SYSTEM_CURSOR_HAND);
		}
		break;
	case STATE_OVER:
		if (!col)
		{
			m_state = STATE_UP;
			EVMA::SetCursor(SDL_SYSTEM_CURSOR_ARROW);
		}
		else if (col && EVMA::MousePressed(1)) m_state = STATE_DOWN; // 1 is left mouse.
		break;
	case STATE_DOWN:
		if (EVMA::MouseReleased(1)) // Left mouse released.
		{
			if (col)
			{
				m_state = STATE_OVER;
				Execute();
			}
			else
			{
				m_state = STATE_UP;
			}
			EVMA::SetCursor(SDL_SYSTEM_CURSOR_ARROW);
		}
		break;
	}
}

void Button3::Render()
{
	m_src.x = m_src.w * (int)m_state; 
	SDL_RenderCopyF(REMA::GetRenderer(), TEMA::GetTexture(m_key), &m_src, &m_dst);
}

PlayButton::PlayButton(SDL_Rect src, SDL_FRect dst, const char* key) :Button3(src, dst, key) {}

void PlayButton::Execute()
{
	STMA::ChangeState(new GameState());
}