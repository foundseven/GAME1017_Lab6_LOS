#include "CollisionManager.h"
#define BUFFER 0.2

bool CollisionManager::AABBCheck(const SDL_Rect& object1, const SDL_Rect& object2)
{
	return SDL_HasIntersection(&object1, &object2);
}

bool CollisionManager::AABBCheck(const SDL_Rect& object1, const SDL_FRect& object2)
{
	SDL_Rect temp = MAMA::ConvertFRect2Rect(object2);
	return SDL_HasIntersection(&object1, &temp);
}

bool CollisionManager::AABBCheck(const SDL_FRect& object1, const SDL_FRect& object2)
{
	return SDL_HasIntersectionF(&object1, &object2);
}

bool CollisionManager::AABBLineCheck(const SDL_Rect& object1, SDL_Point object2Start, SDL_Point object2End)
{
	return SDL_IntersectRectAndLine(&object1, &object2Start.x, &object2Start.y, &object2End.x, &object2End.y);
}

bool CollisionManager::AABBLineCheck(const SDL_FRect& object1, SDL_Point object2Start, SDL_Point object2End)
{
	SDL_Rect temp = MAMA::ConvertFRect2Rect(object1);
	return SDL_IntersectRectAndLine(&temp, &object2Start.x, &object2Start.y, &object2End.x, &object2End.y);
}

bool CollisionManager::AABBLineCheck(const SDL_FRect& object1, SDL_FPoint object2Start, SDL_FPoint object2End)
{
	return SDL_IntersectFRectAndLine(&object1, &object2Start.x, &object2Start.y, &object2End.x, &object2End.y);
}

bool CollisionManager::CircleAABBCheck(const SDL_Point object1, const double radius, const SDL_Rect& object2)
{
	double x1 = (double)object1.x;
	double y1 = (double)object1.y;
	if (object1.x < object2.x) // Circle center, rect left edge.
		x1 = (double)object2.x;
	else if (object1.x > object2.x + object2.w)
		x1 = (double)object2.x + (double)object2.w;
	if (object1.y < object2.y)
		y1 = (double)object2.y;
	else if (object1.y > object2.y + object2.h)
		y1 = (double)object2.y + (double)object2.h;

	return CircleCircleCheck({ (int)x1, (int)y1 }, object1, radius);
}

bool CollisionManager::CircleAABBCheck(const SDL_FPoint object1, const double radius, const SDL_FRect& object2)
{
	double x1 = (double)object1.x;
	double y1 = (double)object1.y;
	if (object1.x < object2.x) // Circle center, rect left edge.
		x1 = (double)object2.x;
	else if (object1.x > object2.x + object2.w)
		x1 = (double)object2.x + (double)object2.w;
	if (object1.y < object2.y)
		y1 = (double)object2.y;
	else if (object1.y > object2.y + object2.h)
		y1 = (double)object2.y + (double)object2.h;

	return CircleCircleCheck({ (float)x1, (float)y1 }, object1, radius);
}

bool CollisionManager::CircleCircleCheck(const SDL_Point object1, const SDL_Point object2, const double radius1, const double radius2)
{
	return (MAMA::Distance((double)object1.x, (double)object2.x, (double)object1.y, (double)object2.y) < (radius1+ radius2));
}

bool CollisionManager::CircleCircleCheck(const SDL_FPoint object1, const SDL_FPoint object2, const double radius1, const double radius2)
{
	return (MAMA::Distance((double)object1.x, (double)object2.x, (double)object1.y, (double)object2.y) < (radius1 + radius2));
}

bool CollisionManager::LinePointCheck(const SDL_Point object1Start, const SDL_Point object1End, const SDL_Point object2)
{
	double distToStart = MAMA::Distance((double)object1Start.x, (double)object2.x, (double)object1Start.y, (double)object2.y);
	double distToEnd = MAMA::Distance((double)object1End.x, (double)object2.x, (double)object1End.y, (double)object2.y);

	double lineLength = MAMA::Distance((double)object1Start.x, (double)object1End.x, (double)object1Start.y, (double)object1End.y);

	double buffer = BUFFER; // Extra distance since line thickness is one pixel.
	
	if (distToStart + distToEnd <= lineLength + buffer)
		return true;
	return false;
}

bool CollisionManager::LinePointCheck(const SDL_FPoint object1Start, const SDL_FPoint object1End, const SDL_FPoint object2)
{
	double distToStart = MAMA::Distance((double)object1Start.x, (double)object2.x, (double)object1Start.y, (double)object2.y);
	double distToEnd = MAMA::Distance((double)object1End.x, (double)object2.x, (double)object1End.y, (double)object2.y);

	double lineLength = MAMA::Distance((double)object1Start.x, (double)object1End.x, (double)object1Start.y, (double)object1End.y);

	double buffer = BUFFER; // Extra distance since line thickness is one pixel.
	
	if (distToStart + distToEnd <= lineLength + buffer)
		return true;
	return false;
}

bool CollisionManager::PointAABBCheck(const SDL_Point object1, const SDL_Rect &object2)
{
	return SDL_PointInRect(&object1, &object2);
}

bool CollisionManager::PointAABBCheck(const SDL_Point object1, const SDL_FRect &object2)
{
	SDL_Rect temp = MAMA::ConvertFRect2Rect(object2);
	return SDL_PointInRect(&object1, &temp);
}

bool CollisionManager::PointAABBCheck(const SDL_FPoint object1, const SDL_FRect &object2)
{
	return SDL_PointInFRect(&object1, &object2);
}

bool CollisionManager::LOSCheck(SDL_FPoint begin, SDL_FPoint end, SDL_FRect* target, std::vector<Tile*>& obstacles)
{
	// Check collision with obstacles first.
	for (auto obstacle : obstacles)
	{
		if (SDL_IntersectFRectAndLine(obstacle->GetDst(), &begin.x, &begin.y, &end.x, &end.y))
		{
			return false;
		}
	}
	// Now check if hitting target.
	if (SDL_IntersectFRectAndLine(target, &begin.x, &begin.y, &end.x, &end.y))
	{
		return true;
	}
	// Nothing hit.
	return false;
}
