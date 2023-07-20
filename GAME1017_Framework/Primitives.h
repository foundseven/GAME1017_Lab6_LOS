#ifndef __PRIMITIVES_H__
#define __PRIMITIVES_H__
#include "GameObject.h"
#include <SDL_ttf.h>
#include <string>

class Image : public Sprite
{
public:
	Image(SDL_Rect src, SDL_FRect dst , const char* key);
	void Update() {};
	void Render();
private:
	std::string m_key;
};

class Line : public GameObject
{
public:
	Line(SDL_FPoint start, SDL_FPoint end, SDL_Color col = { 255, 255, 255, 255 });
	void Update() {};
	void Render();
private:
	SDL_FPoint m_start, m_end;
	SDL_Color m_color;
};

class Rectangle : public GameObject
{
public:
	Rectangle(SDL_FRect dst, bool fill, SDL_Color col = { 255, 255, 255, 255 });
	void Update() {};
	void Render();
private:
	bool m_fill;
	SDL_Color m_color;
};

class Label : public GameObject
{
public: // Public methods.
	Label(std::string key, const float x, const float y, const char* str, const SDL_Color col = { 255,255,255,255 });
	~Label();
	void Update() {}
	void Render();
	const char* GetText() const { return m_string; }
	void SetText(const char* c);
	void SetPos(const float x, const float y);
	void SetColor(const SDL_Color& col);
	void UseFont(std::string key);

private: // Private properties.
	TTF_Font* m_font;
	SDL_Color m_textColor;
	SDL_Rect m_textRect;
	SDL_Texture* m_pTexture; // Fonts manage their own texture for now.
	char m_string[256];
};

#endif