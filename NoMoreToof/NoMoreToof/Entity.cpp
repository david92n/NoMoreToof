#include "Entity.h"
#include "ResourceHandler.h"
#include <cmath>

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
	sf::Vector2f pixelPerfectPos(round(m_position.x + m_spriteOffset.x), round(m_position.y + m_spriteOffset.y));
	m_sprite->setPosition(pixelPerfectPos);
	renderTarget.draw(*m_sprite);
}
