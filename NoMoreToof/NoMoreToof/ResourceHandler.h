#pragma once
#include <map>
#include <SFML/Graphics.hpp>
static class ResourceHandler
{
public:
	static sf::Texture* LoadTexture(const std::string& path);
	static void UnloadTexture(const std::string& path);
	static void UnloadAllTextures();

	static sf::Font* LoadFont(const std::string& path);
	static void UnloadFont(const std::string& path);
	static void UnloadAllFonts();
private:
	static std::map<std::string, sf::Texture*> _textures;
	static std::map<std::string, sf::Font*> _fonts;
};

