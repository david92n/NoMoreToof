#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity(const std::string& texturePath);
	virtual ~Entity();

	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderTarget& renderTarget);
protected:
	sf::Vector2f m_spriteOffset;
	sf::Vector2f m_position;
private:
	sf::Sprite* m_sprite;
};

