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

sf::Vector2f Entity::GetPosition()
{
	return m_position;
}

void Entity::SetPosition(sf::Vector2f position)
{
	m_position = position;
}

sf::Vector2f Entity::GetStartPosition()
{
	return m_startPosition;
}

void Entity::SetStartPosition(sf::Vector2f position)
{
	m_startPosition = position;
}

sf::Vector2f Entity::GetTargetPosition()
{
	return m_targetPosition;
}

void Entity::SetTargetPosition(sf::Vector2f position)
{
	m_targetPosition = position;
}
