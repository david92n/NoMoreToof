#include "DialogueBox.h"
#include "ResourceHandler.h"

DialogueBox::DialogueBox() : m_active(false), m_currentPlacementOffset(DialogueBox::UPPERLEFT)
{
	m_box.setTexture(*ResourceHandler::LoadTexture("res/dialoguebox.png"));
	m_arrow.setTexture(*ResourceHandler::LoadTexture("res/dialoguetails.png"));
	m_next.setTexture(*ResourceHandler::LoadTexture("res/arrow_exit.png"));
}

DialogueBox::~DialogueBox()
{

}

bool DialogueBox::GetActive()
{
	return m_active;
}

void DialogueBox::SetActive(bool active)
{
	m_active = active;
}

void DialogueBox::SetLines()
{
}

sf::Vector2f DialogueBox::GetPosition()
{
	return m_position;
}

void DialogueBox::SetPosition(sf::Vector2f position)
{
	m_position = position;
}

void DialogueBox::Render(sf::RenderTarget& renderTarget)
{
	if (!m_active) return;

	sf::Vector2f pixelPerfectPos(round(m_position.x + m_placementOffsets[m_currentPlacementOffset].x), round(m_position.y + m_placementOffsets[m_currentPlacementOffset].y));
	m_box.setPosition(pixelPerfectPos);
	renderTarget.draw(m_box);

	m_arrow.setPosition(pixelPerfectPos + m_arrowPosition);
	renderTarget.draw(m_arrow);
}

sf::Vector2u DialogueBox::GetSpriteSize()
{
	return m_box.getTexture()->getSize();
}

void DialogueBox::SetPlacementOffsets(sf::Vector2f offsets[4])
{
	m_placementOffsets[0] = offsets[0];
	m_placementOffsets[1] = offsets[1];
	m_placementOffsets[2] = offsets[2];
	m_placementOffsets[3] = offsets[3];
}

void DialogueBox::SetOffsetLocation(DialogueBox::Placement placementOffset)
{
	m_currentPlacementOffset = placementOffset;

	sf::IntRect arrowRect(0, 0, m_arrow.getTexture()->getSize().x, m_arrow.getTexture()->getSize().y * 0.5f);

	switch (placementOffset)
	{
	case DialogueBox::UPPERLEFT:
		m_arrowPosition.x = 100.0f;
		m_arrowPosition.y = 73.0f;
		arrowRect.top = arrowRect.height;
		break;
	case DialogueBox::UPPERRIGHT:
		m_arrowPosition.x = 10.0f;
		m_arrowPosition.y = 73.0f;
		arrowRect.top = arrowRect.height;
		break;
	case DialogueBox::LOWERLEFT:
		m_arrowPosition.x = 100.0f;
		m_arrowPosition.y = -6.0f;
		break;
	case DialogueBox::LOWERRIGHT:
		m_arrowPosition.x = 10.0f;
		m_arrowPosition.y = -6.0f;
		break;
	}

	m_arrow.setTextureRect(arrowRect);
}