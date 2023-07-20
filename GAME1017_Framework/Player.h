#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameObject.h"
#include "TiledLevel.h"

class Player : public AnimatedSprite
{
public:
	Player(SDL_Rect s, SDL_FRect d, TiledLevel* level);
	void Update();
	void Render();
private:
	bool m_dir;
	TiledLevel* m_level;
	bool CheckCollision(const int dX, const int dY);
};

#endif

