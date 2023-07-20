#include "Primitives.h"
#include "FontManager.h"
#include "RenderManager.h"
#include "TextureManager.h"

Image::Image(SDL_Rect src, SDL_FRect dst, const char* key) :Sprite(src, dst), m_key(key) {}

void Image::Render()
{
	SDL_RenderCopyF(REMA::GetRenderer(), TEMA::GetTexture(m_key), &m_src, &m_dst);
}

Line::Line(SDL_FPoint start, SDL_FPoint end, SDL_Color col) :
	GameObject({ 0,0,0,0 }), m_start(start), m_end(end), m_color(col) {}

void Line::Render()
{
	SDL_SetRenderDrawColor(REMA::GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderDrawLineF(REMA::GetRenderer(), m_start.x, m_start.y, m_end.x, m_end.y);
}

Rectangle::Rectangle(SDL_FRect dst, bool fill, SDL_Color col) :
	GameObject(dst), m_fill(fill), m_color(col) {}

void Rectangle::Render()
{
	SDL_SetRenderDrawColor(REMA::GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
	if (m_fill)
		SDL_RenderFillRectF(REMA::GetRenderer(), &m_dst);
	else
		SDL_RenderDrawRectF(REMA::GetRenderer(), &m_dst);
}

Label::Label(std::string key, const float x, const float y, const char* str,
	const SDL_Color col) :m_textColor(col)
{
	m_font = FOMA::GetFont(key);
	SetPos(x, y);
	SetText(str);
}

Label::~Label()
{
	SDL_DestroyTexture(m_pTexture);
}

void Label::Render()
{
	SDL_RenderCopyF(REMA::GetRenderer(), m_pTexture, NULL, &m_dst);
}

void Label::SetText(const char* str)
{
	strcpy_s(m_string, 256, str);
	SDL_Surface* fontSurf = TTF_RenderText_Blended(m_font, m_string, m_textColor);
	SDL_DestroyTexture(m_pTexture);
	m_pTexture = SDL_CreateTextureFromSurface(REMA::GetRenderer(), fontSurf);
	m_dst = { m_dst.x, m_dst.y, (float)fontSurf->w, (float)fontSurf->h };
	SDL_FreeSurface(fontSurf);
}

void Label::SetPos(const float x, const float y)
{
	m_dst = { x, y, (float)m_dst.w, (float)m_dst.h };
}

void Label::SetColor(const SDL_Color& col)
{
	// Change to use tint and invert color with a bitwise XOR (tint ^= color)
	m_textColor = col;
	SetText(m_string);
}

void Label::UseFont(std::string key)
{
	m_font = FOMA::GetFont(key);
	SetText(m_string);
}