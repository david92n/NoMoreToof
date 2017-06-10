#pragma once
#include "Entity.h"
#include "OneAnimation.h"

class EntityNPC :
	public Entity
{
public:
	EntityNPC(const std::string& texturePath, sf::Vector2f position, sf::Vector2f shadowOffset, int animRows, int animCols, int numFrames, float frameTime);
	~EntityNPC();

	void Update(float deltaTime);
	void Render(sf::RenderTarget& renderTarget);
private:
	OneAnimation m_animIdle;
};

