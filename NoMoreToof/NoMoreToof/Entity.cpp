#include "Entity.h"
#include "ResourceHandler.h"


Entity::Entity(const std::string& texturePath)
{
	m_sprite = new sf::Sprite(*ResourceHandler::LoadTexture(texturePath));
}


Entity::~Entity()
{
	delete m_sprite;
}

void Entity::Render(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(*m_sprite);
}
