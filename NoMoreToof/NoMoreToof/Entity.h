#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity(const std::string& texturePath);
	virtual ~Entity();

	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderTarget& renderTarget);

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position);

	sf::Vector2f GetRootPosition();
	void SetRootPosition(sf::Vector2f position);

	sf::Vector2f GetStartPosition();
	void SetStartPosition(sf::Vector2f position);

	sf::Vector2f GetTargetPosition();
	void SetTargetPosition(sf::Vector2f position);
protected:
	sf::Vector2f m_spriteOffset;
	sf::Vector2f m_position;
	sf::Vector2f m_rootPosition;
private:
	sf::Vector2f m_startPosition;
	sf::Vector2f m_targetPosition;

	sf::Sprite* m_sprite;
};

