#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity(const std::string& texturePath);
	~Entity();



	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderTarget& renderTarget);

private:
	sf::Sprite* m_sprite;
};

