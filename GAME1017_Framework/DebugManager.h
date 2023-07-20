#ifndef __DEBUGMANAGER_H__
#define __DEBUGMANAGER_H__
#include "SDL_rect.h"

class DebugManager
{
public:
	static void DrawLine(const SDL_Point start, const SDL_Point end, const SDL_Color col = {255, 255, 255, 255});
	static void DrawLine(const SDL_FPoint start, const SDL_FPoint end, const SDL_Color col = {255, 255, 255, 255});
	static void DrawRect(const SDL_Rect rect, bool fill = false, const SDL_Color col = { 255, 255, 255, 255 });
	static void DrawRect(const SDL_FRect rect, bool fill = false, const SDL_Color col = { 255, 255, 255, 255 });
};

typedef DebugManager DEMA;

#endif
