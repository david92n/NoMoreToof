#include "SpriteAnimation.h"
#include "ResourceHandler.h"

SpriteAnimation::SpriteAnimation(const std::string& texturePath, int numRows, int numCols, float frameTime)
	: m_numRows(numRows), m_numCols(numCols), m_frameTime(frameTime), m_currentCol(0), m_currentRow(0), m_currentTimer(0.0f)
{
	m_sprite = new sf::Sprite(*ResourceHandler::LoadTexture(texturePath));

	sf::Vector2u textureSize = m_sprite->getTexture()->getSize();

	m_frameWidth = textureSize.x / numCols;
	m_frameHeight = textureSize.y / numRows;
}

SpriteAnimation::~SpriteAnimation()
{
	delete m_sprite;
}

void SpriteAnimation::SetAnimation(int animIndex)
{
	m_currentRow = animIndex;
}

void SpriteAnimation::SetPosition(sf::Vector2f position)
{
	sf::Vector2f pixelPerfectPos(round(position.x), round(position.y));
	m_sprite->setPosition(pixelPerfectPos);
}

void SpriteAnimation::Update(float deltaTime)
{
	m_currentTimer += deltaTime;

	if (m_currentTimer >= m_frameTime)
	{
		m_currentTimer -= m_frameTime;
		m_currentCol = (m_currentCol + 1) % m_numCols;
	}
}

void SpriteAnimation::Render(sf::RenderTarget& renderTarget)
{
	m_sprite->setTextureRect(sf::IntRect(m_currentCol * m_frameWidth, m_currentRow * m_frameHeight, m_frameWidth, m_frameHeight));
	renderTarget.draw(*m_sprite);
}

sf::Vector2u SpriteAnimation::GetSpriteSize()
{
	return sf::Vector2u(m_frameWidth, m_frameHeight);
}