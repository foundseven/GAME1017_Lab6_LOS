#pragma once
#ifndef __TILEDLEVEL_H__
#define __TILEDLEVEL_H__

#include <fstream>
#include <map>
#include <vector>
#include "Primitives.h"

class Tile : public Sprite
{
public:
	Tile(SDL_Rect src, SDL_FRect dst, bool isObs, bool isHaz);
	~Tile();
	Tile* Clone() {	return new Tile(m_src, m_dst, m_obstacle, m_hazard); }
	bool IsObstacle() { return m_obstacle; }
	bool IsHazard() { return m_hazard; }
	void SetXY(float x, float y) { m_dst.x = x; m_dst.y = y; }
	void Update() {}
	void Render() {}
private:
	bool m_obstacle, m_hazard;
};

class TiledLevel : public GameObject
{
public:
	TiledLevel(const unsigned short r, const unsigned short c, const int w, const int h,
		const char* tileData, const char* levelData, const char* tileKey);
	~TiledLevel();
	void Update() {} // Empty.
	void Render();
	std::vector<Tile*>& GetObstacles();
	std::vector<std::vector<Tile*>>& GetLevel();

private:
	const char* m_tileKey;
	int m_rows, m_cols;
	std::map<char, Tile*> m_tiles; // Our map of prototype Tile objects.
	std::vector<std::vector<Tile*>> m_level; // 2D vector.
	std::vector<Tile*> m_obstacles;
};

#endif

