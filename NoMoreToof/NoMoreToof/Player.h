#pragma once
#include "Entity.h"
class Player :
	public Entity
{
public:
	Player();
	~Player();

	virtual void Update(float deltaTime);
	virtual void Render(sf::RenderTarget& renderTarget);
};

