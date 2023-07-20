#include "DebugManager.h"
#include "RenderManager.h"

void DebugManager::DrawLine(const SDL_Point start, const SDL_Point end, const SDL_Color col)
{
	SDL_SetRenderDrawColor(REMA::GetRenderer(), col.r, col.g, col.b, col.a);
	SDL_RenderDrawLine(REMA::GetRenderer(), start.x, start.y, end.x, end.y);
}

void DebugManager::DrawLine(const SDL_FPoint start, const SDL_FPoint end, const SDL_Color col)
{
	SDL_SetRenderDrawColor(REMA::GetRenderer(), col.r, col.g, col.b, col.a);
	SDL_RenderDrawLineF(REMA::GetRenderer(), start.x, start.y, end.x, end.y);
}

void DebugManager::DrawRect(const SDL_Rect rect, bool fill, const SDL_Color col)
{
	SDL_SetRenderDrawColor(REMA::GetRenderer(), col.r, col.g, col.b, col.a);
	if (fill = true)
		SDL_RenderFillRect(REMA::GetRenderer(), &rect);
	else
		SDL_RenderDrawRect(REMA::GetRenderer(), &rect);
}

void DebugManager::DrawRect(const SDL_FRect rect, bool fill, const SDL_Color col)
{
	SDL_SetRenderDrawColor(REMA::GetRenderer(), col.r, col.g, col.b, col.a);
	if (fill = true)
		SDL_RenderFillRectF(REMA::GetRenderer(), &rect);
	else
		SDL_RenderDrawRectF(REMA::GetRenderer(), &rect);
}
