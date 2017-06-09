#include "ResourceHandler.h"

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
	}

	return texture;
}