#include "OneAnimation.h"
#include "ResourceHandler.h"

OneAnimation::OneAnimation(const std::string& texturePath, int numRows, int numCols, int numFrames, float frameTime, bool playOnce)
	: m_numRows(numRows), m_numCols(numCols), m_numFrames(numFrames), m_frameTime(frameTime), m_currentCol(0), m_currentRow(0), m_currentFrame(0), m_currentTimer(0.0f), m_playOnce(playOnce), m_isDone(false)
{
	m_sprite = new sf::Sprite(*ResourceHandler::LoadTexture(texturePath));

	sf::Vector2u textureSize = m_sprite->getTexture()->getSize();

	m_frameWidth = textureSize.x / numCols;
	m_frameHeight = textureSize.y / numRows;
}

OneAnimation::~OneAnimation()
{
	delete m_sprite;
}

void OneAnimation::SetPosition(sf::Vector2f position)
{
	sf::Vector2f pixelPerfectPos(round(position.x), round(position.y));
	m_sprite->setPosition(pixelPerfectPos);
}

void OneAnimation::Update(float deltaTime)
{
	if (m_isDone) return;

	m_currentTimer += deltaTime;

	if (m_currentTimer >= m_frameTime)
	{
		m_currentTimer -= m_frameTime;

		if (m_playOnce)
		{
			if (++m_currentFrame == m_numFrames)
			{
				m_isDone = true;
			}
		}
		else
		{
			m_currentFrame = (m_currentFrame + 1) % m_numFrames;
		}

		m_currentCol = m_currentFrame % m_numCols;
		m_currentRow = m_currentFrame / m_numCols;
	}
}

void OneAnimation::Render(sf::RenderTarget& renderTarget)
{
	m_sprite->setTextureRect(sf::IntRect(m_currentCol * m_frameWidth, m_currentRow * m_frameHeight, m_frameWidth, m_frameHeight));
	renderTarget.draw(*m_sprite);
}

sf::Vector2u OneAnimation::GetSpriteSize()
{
	return sf::Vector2u(m_frameWidth, m_frameHeight);
}
