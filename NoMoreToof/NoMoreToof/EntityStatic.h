#pragma once
#include "Entity.h"
class EntityStatic :
	public Entity
{
public:
	EntityStatic();
	~EntityStatic();

	virtual void Update(float deltaTime);
	virtual void Render(sf::RenderTarget& renderTarget);
};

