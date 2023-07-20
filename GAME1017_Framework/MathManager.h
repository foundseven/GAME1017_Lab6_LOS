#ifndef __MATHMANAGER_H__
#define __MATHMANAGER_H__
#include <algorithm>
#include <cmath>
#include "SDL.h"

class MathManager
{
public: // Public methods.
	static double Distance(const double& x1, const double& x2, const double& y1, const double& y2);
	static double Distance(const SDL_FRect* r1, const SDL_FRect* r2);
	static double Distance(const SDL_FPoint p1, const SDL_FPoint p2);
	static double Distance(const SDL_FPoint* p1, const SDL_FPoint* p2);
	static SDL_FPoint Normalize(SDL_FPoint vec);
	static double AngleBetweenPoints(const double dy, const double dx);
	static void SetDeltas(const double angle, double& dx, double& dy, double fx, double fy);
	static double SetDeltaX(const double angle, double fx = 1.0);
	static double SetDeltaY(const double angle, double fy = 1.0);
	static double Deg2Rad(const double angle);
	static double Rad2Deg(const double angle);
	static SDL_Rect ConvertFRect2Rect(const SDL_FRect& r);
	static SDL_Point ConvertFPoint2Point(const SDL_FPoint& p);
	static double Angle180(double angle);
	static double Angle360(double angle);
	static double LerpD(double a, double b, double factor);
	static double LerpRad(double a, double b, double factor);
	static SDL_Point HalfwayPoint(const SDL_Point& from, const SDL_Point& to);
	static SDL_FPoint HalfwayPoint(const SDL_FPoint& from, const SDL_FPoint& to);
	static int Clamp(const int a, const int min, const int max);
	static float Clamp(const float a, const float min, const float max);

private: // Private properties.
	MathManager() = default;
};

typedef MathManager MAMA;

#endif