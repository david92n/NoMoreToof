#include "ResourceHandler.h"
#include <iostream>

std::map<std::string, sf::Texture*> ResourceHandler::_textures;
std::map<std::string, sf::Font*> ResourceHandler::_fonts;

sf::Texture* ResourceHandler::LoadTexture(const std::string& path)
{
	std::string texturePath = "res/textures/" + path + ".png";

	sf::Texture* texture = _textures[texturePath];
	
	if (texture == nullptr)
	{
		texture = new sf::Texture();
		if (texture->loadFromFile(texturePath))
		{
			_textures[texturePath] = texture;
		}
		else
		{
			std::cout << "Can't load " << texturePath << "\n";
		}
	}

	return texture;
}


void ResourceHandler::UnloadTexture(const std::string& path)
{
	std::string texturePath = "res/textures/" + path + ".png";

	sf::Texture* texture = _textures[texturePath];

	if (texture != nullptr)
	{
		delete texture;
		_textures.erase(texturePath);
	}
}

void ResourceHandler::UnloadAllTextures()
{
	std::map<std::string, sf::Texture*>::iterator it;
	for (it = _textures.begin(); it != _textures.end(); ++it)
	{
		delete it->second;
	}
	_textures.clear();
}

sf::Font* ResourceHandler::LoadFont(const std::string& path)
{
	sf::Font* font = _fonts[path];

	if (font == nullptr)
	{
		font = new sf::Font();

		if (font->loadFromFile(path))
		{
			sf::Texture& texture = const_cast<sf::Texture&>(font->getTexture(12u));
			texture.setSmooth(false);
			_fonts[path] = font;
		}
		else
		{
			std::cout << "Can't load " << path << "\n";
		}
	}

	return font;
}


void ResourceHandler::UnloadFont(const std::string& path)
{
	sf::Font* font = _fonts[path];

	if (font != nullptr)
	{
		delete font;
		_fonts.erase(path);
	}
}

void ResourceHandler::UnloadAllFonts()
{
	std::map<std::string, sf::Font*>::iterator it;
	for (it = _fonts.begin(); it != _fonts.end(); ++it)
	{
		delete it->second;
	}
	_fonts.clear();
}