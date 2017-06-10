#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <string>

class SpriteAnimation
{
public:
	SpriteAnimation(const std::string& texturePath, int numRows, int numCols, float frameTime);
	~SpriteAnimation();

	void SetAnimation(int animIndex);
	void SetPosition(sf::Vector2f position);
	
	void Update(float deltaTime);
	void Render(sf::RenderTarget& renderTarget);

	sf::Vector2u GetSpriteSize();

private:
	sf::Sprite* m_sprite;
	
	unsigned int m_frameWidth, m_frameHeight;
	int m_numRows, m_numCols;
	float m_frameTime;

	float m_currentTimer;
	int m_currentRow, m_currentCol;
};

