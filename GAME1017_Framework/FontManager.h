#pragma once
#ifndef _FONTMANAGER_H_
#define _FONTMANAGER_H_

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class FontManager
{
public: // Public methods.
	static void Load(const char* path, const std::string key, const int size);
	static void Unload(const std::string key);
	static void SetSize(const char* path, const std::string key, const int size);
	static TTF_Font* GetFont(const std::string key);
	static void Quit();
private: // Private properties.
	static std::map<std::string, TTF_Font*> s_fonts;
private: // Private methods.
	FontManager() {}
};

typedef FontManager FOMA;

#endif