#include "ResourceHandler.h"
#include <iostream>

std::map<std::string, sf::Texture*> ResourceHandler::_textures;

sf::Texture* ResourceHandler::LoadTexture(const std::string& path)
{
	sf::Texture* texture = _textures[path];
	
	if (texture == nullptr)
	{
		texture = new sf::Texture();
		if (texture->loadFromFile(path))
		{
			_textures[path] = texture;
		}
		else
		{
			std::cout << "Can't load " << path << "\n";
		}
	}

	return texture;
}


void ResourceHandler::UnloadTexture(const std::string& path)
{
	sf::Texture* texture = _textures[path];

	if (texture != nullptr)
	{
		delete texture;
		_textures.erase(path);
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