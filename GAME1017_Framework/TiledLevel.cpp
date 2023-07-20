#include "TiledLevel.h"
#include "RenderManager.h"
#include "TextureManager.h"
#include "MathManager.h"
#include "Engine.h"
#include <string>


Tile::Tile(SDL_Rect src, SDL_FRect dst, bool isObs, bool isHaz)
	:Sprite(src, dst), m_obstacle(isObs), m_hazard(isHaz) {}

Tile::~Tile(){}

TiledLevel::TiledLevel(const unsigned short rows, const unsigned short cols, const int tileWidth, const int tileHeight, 
	const char* tileData, const char* levelData, const char* tileKey) 
	:m_rows(rows), m_cols(cols), m_tileKey(tileKey)
{
	// First build prototype tiles.
	std::ifstream inFile(tileData);
	if (inFile.is_open()) 
	{
		char key;
		int x, y;
		bool obs, haz;
		while (!inFile.eof())
		{
			inFile >> key >> x >> y >> obs >> haz;
			m_tiles.emplace(key, new Tile({ x * tileWidth, y * tileHeight, tileWidth, tileHeight },
				{ 0.0f, 0.0f, (float)tileWidth, (float)tileHeight }, obs, haz));
		}
	}
	inFile.close();
	// Now construct the level.
	inFile.open(levelData);
	if (inFile.is_open()) 
	{
		char key;
		m_level.resize(m_rows); // Important or we cannot use subscripts.
		for (unsigned short row = 0; row < m_rows; row++)
		{
			m_level[row].resize(m_cols);
			for (unsigned short col = 0; col < m_cols; col++)
			{
				inFile >> key;
				m_level[row][col] = m_tiles[key]->Clone(); // Common prototype method.
				m_level[row][col]->SetXY((float)(col * tileWidth), (float)(row * tileHeight));
				// Add tile to Obstacle vector if impassable.
				if (m_level[row][col]->IsObstacle())
					m_obstacles.push_back(m_level[row][col]);
			}
		}
	}
	inFile.close();
}

TiledLevel::~TiledLevel()
{
	// Clear the tile clones. This also clears the ones in m_obstacles.
	for (unsigned short row = 0; row < m_rows; row++)
	{
		for (unsigned short col = 0; col < m_cols; col++)
		{
			delete m_level[row][col];
			m_level[row][col] = nullptr;
		}
	}
	m_level.clear();
	m_obstacles.clear();
	// Clear the original tiles.
	for (std::map<char, Tile*>::iterator i = m_tiles.begin(); i != m_tiles.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}
	m_tiles.clear();
}

void TiledLevel::Render()
{
	for (unsigned short row = 0; row < m_rows; row++)
	{
		for (unsigned short col = 0; col < m_cols; col++)
		{
			SDL_RenderCopyF(REMA::GetRenderer(), TEMA::GetTexture(m_tileKey),
				m_level[row][col]->GetSrc(), m_level[row][col]->GetDst());
		}
	}
}

std::vector<Tile*>& TiledLevel::GetObstacles() { return m_obstacles; }

std::vector<std::vector<Tile*>>& TiledLevel::GetLevel() { return m_level; }
