#ifndef __COLLISIONMANAGER_H__
#define __COLLISIONMANAGER_H__
#include <iostream>
#include <SDL.h>
#include <vector>
#include "MathManager.h"
#include "TiledLevel.h"

class CollisionManager
{
public:
	// AABB-AABB overloads.
	static bool AABBCheck(const SDL_Rect& object1, const SDL_Rect& object2); // Two int-based Rects.
	static bool AABBCheck(const SDL_Rect& object1, const SDL_FRect& object2); // Int-based Rect, Float-based Rect.
	static bool AABBCheck(const SDL_FRect& object1, const SDL_FRect& object2); // Two float-based Rects.

	// AABB-Line overloads.
	static bool AABBLineCheck(const SDL_Rect& object1, SDL_Point object2Start, SDL_Point object2End); // Int-based.
	static bool AABBLineCheck(const SDL_FRect& object1, SDL_Point object2Start, SDL_Point object2End); // Int-based line, Float-based Rect.
	static bool AABBLineCheck(const SDL_FRect& object1, SDL_FPoint object2Start, SDL_FPoint object2End); // Float-based.

	// Circle-AABB overloads.
	static bool CircleAABBCheck(const SDL_Point object1, const double radius, const SDL_Rect& object2); // Int-based.
	static bool CircleAABBCheck(const SDL_FPoint object1, const double radius, const SDL_FRect& object2); // Float-based.

	// Circle-Circle overloads.
	static bool CircleCircleCheck(const SDL_Point object1, const SDL_Point object2, 
		const double radius1, const double radius2 = 0.0); // Int-based.
	static bool CircleCircleCheck(const SDL_FPoint object1, const SDL_FPoint object2, 
		const double radius1, const double radius2 = 0.0); // Float-based.
	
	// Line-Point overloads.
	static bool LinePointCheck(const SDL_Point object1Start, const SDL_Point object1End, const SDL_Point object2); // Int-based.
	static bool LinePointCheck(const SDL_FPoint object1Start, const SDL_FPoint object1End, const SDL_FPoint object2); // Float-based.

	// Point-AABB overloads.
	static bool PointAABBCheck(const SDL_Point object1, const SDL_Rect& object2); // Int-based.
	static bool PointAABBCheck(const SDL_Point object1, const SDL_FRect& object2); // Int-based point, Float-based Rect.
	static bool PointAABBCheck(const SDL_FPoint object1, const SDL_FRect& object2); // Float-based.

	// LOS check. New.
	static bool LOSCheck(SDL_FPoint begin, SDL_FPoint end, SDL_FRect* target, std::vector<Tile*>& obstacles);

private:
	CollisionManager() = default;
};

typedef CollisionManager COMA;

#endif