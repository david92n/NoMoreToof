#pragma once
#include <map>
#include <SFML/Graphics.hpp>
static class ResourceHandler
{
public:
	static sf::Texture* LoadTexture(const std::string& path);
	//static void UnloadTexture(const std::string& path);

	//static void UnloadAll();
private:
	static std::map<std::string, sf::Texture*> _textures;
};

