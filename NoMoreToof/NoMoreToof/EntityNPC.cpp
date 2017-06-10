#include "EntityNPC.h"

EntityNPC::EntityNPC(const std::string& texturePath, sf::Vector2f position, sf::Vector2f shadowOffset, int animRows, int animCols, int numFrames, float frameTime)
	: Entity("shadow"), m_animIdle(texturePath, animRows, animCols, numFrames, frameTime)
{
	m_spriteOffset.x = shadowOffset.x;
	m_spriteOffset.y = shadowOffset.y;

	m_position = position;
}

EntityNPC::~EntityNPC()
{
}

void EntityNPC::Update(float deltaTime)
{
	m_animIdle.Update(deltaTime);
}

void EntityNPC::Render(sf::RenderTarget& renderTarget)
{
	Entity::Render(renderTarget);

	m_animIdle.SetPosition(m_rootPosition + m_position);
	m_animIdle.Render(renderTarget);
}