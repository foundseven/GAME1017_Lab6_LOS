#include "FontManager.h"
#include <iostream>

void FontManager::Load(const char * path, const std::string key, const int size)
{
	if (!TTF_WasInit())
	{
		if (TTF_Init() == 0)
			std::cout << "Font init success!" << std::endl;
		else
		{
			std::cout << "Font init failed: Error - " << TTF_GetError() << std::endl;
			return;
		}
	}
	TTF_Font* temp = TTF_OpenFont(path, size);
	if (temp == nullptr)
		std::cout << "Could not load font: Error - " << TTF_GetError() << std::endl;
	else
	{
		std::cout << "Font with key '" << key << "' registered successfully!" << std::endl;
		s_fonts.emplace(key, temp);
	}
}

void FontManager::Unload(const std::string key)
{
	if (s_fonts.find(key) != s_fonts.end())
	{
		TTF_CloseFont(s_fonts[key]);
		s_fonts.erase(key);
	}
	else
		std::cout << "Could not unload '" << key << "' - id not found!" << std::endl;
}

void FontManager::SetSize(const char * path, const std::string key, const int size)
{
	if (s_fonts[key] != nullptr)
	{
		TTF_CloseFont(s_fonts[key]);
		s_fonts.erase(key);
	}
	Load(path, key, size);
}

TTF_Font * FontManager::GetFont(const std::string key)
{
	return s_fonts[key];
}

void FontManager::Quit()
{
	for (auto const& i : s_fonts)
	{
		TTF_CloseFont(s_fonts[i.first]);
	}
	s_fonts.clear();
}

std::map<std::string, TTF_Font*> FontManager::s_fonts;