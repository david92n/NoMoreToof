#include "DialogueBox.h"
#include "ResourceHandler.h"

DialogueBox::DialogueBox() : m_active(false), m_currentPlacementOffset(DialogueBox::UPPERLEFT),
	m_currentStringIndex(0), m_currentSubstrLen(1), m_isSpeed(false), m_isDone(false), m_timer(0.0f)
{
	m_box.setTexture(*ResourceHandler::LoadTexture("dialoguebox"));
	m_arrow.setTexture(*ResourceHandler::LoadTexture("dialoguetails"));
	m_next.setTexture(*ResourceHandler::LoadTexture("arrow_exit"));

	m_text.setFont(*ResourceHandler::LoadFont("res/fonts/manaspc.ttf"));
	m_text.setCharacterSize(12u);

	m_dialogueStrings.push_back("Hello, I am\nToof, please\nhelp me find\nthe king!");
	m_dialogueStrings.push_back("I think he is\nhiding\nsomewhere\naround here!");
	m_text.setString("");
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
	if (m_active) return;

	m_active = active;

	m_currentStringIndex = 0;
	m_currentSubstrLen = 1;
	m_text.setString("");

	SetNextArrow(true);
}

void DialogueBox::SetLines(std::vector<std::string> lines)
{
	m_dialogueStrings = lines;
}

sf::Vector2f DialogueBox::GetPosition()
{
	return m_position;
}

void DialogueBox::SetPosition(sf::Vector2f position)
{
	m_position = position;
}

void DialogueBox::PollEvent(sf::Event& e)
{
	if (!m_active) return;

	if (e.type == sf::Event::KeyPressed)
	{
		switch (e.key.code)
		{
		case sf::Keyboard::Z:
			if (m_isDone)
			{
				if (m_currentStringIndex + 1 >= m_dialogueStrings.size())
				{
					m_active = false;
				}
				else
				{
					++m_currentStringIndex;

					m_currentSubstrLen = 1;
					m_text.setString("");
				}

				m_isDone = false;
				m_isSpeed = false;
			}
			else
			{
				m_isSpeed = true;
			}
			
			break;
		}
	}
}

void DialogueBox::Update(float deltaTime)
{
	if (!m_active) return;

	if (m_currentSubstrLen == m_dialogueStrings[m_currentStringIndex].size() + 1)
	{
		m_isDone = true;
		if (m_currentStringIndex + 1 >= m_dialogueStrings.size())
		{
			SetNextArrow(false);
		}
		return;
	}

	m_timer += deltaTime;

	float textTime = m_isSpeed ? 0.02f : 0.05f;

	/*
	if (m_currentStringIndex <= m_dialogueString.size() + 1 && m_dialogueString[m_currentStringIndex - 1] == ' ')
	{
		textTime *= 4.0f;
	}
	*/

	if (m_timer > textTime)
	{
		m_timer -= textTime;
		m_text.setString(m_dialogueStrings[m_currentStringIndex].substr(0, m_currentSubstrLen++));
	}
}

void DialogueBox::Render(sf::RenderTarget& renderTarget)
{
	if (!m_active) return;

	sf::Vector2f pixelPerfectPos(round(m_position.x + m_placementOffsets[m_currentPlacementOffset].x), round(m_position.y + m_placementOffsets[m_currentPlacementOffset].y));
	m_box.setPosition(pixelPerfectPos);
	renderTarget.draw(m_box);

	m_arrow.setPosition(pixelPerfectPos + m_arrowPosition);
	renderTarget.draw(m_arrow);
	
	m_next.setPosition(pixelPerfectPos + sf::Vector2f(109.0f, 62.0f));
	renderTarget.draw(m_next);

	m_text.setPosition(pixelPerfectPos + sf::Vector2f(3.0f, 3.0f));
	renderTarget.draw(m_text);
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
		m_arrow.setScale(1.0f, 1.0f);
		break;
	case DialogueBox::UPPERRIGHT:
		m_arrowPosition.x = 10.0f;
		m_arrowPosition.y = 73.0f;
		arrowRect.top = arrowRect.height;
		m_arrow.setScale(1.0f, 1.0f);
		break;
	case DialogueBox::LOWERLEFT:
		m_arrowPosition.x = 108.0f;
		m_arrowPosition.y = -6.0f;
		m_arrow.setScale(-1.0f, 1.0f);
		break;
	case DialogueBox::LOWERRIGHT:
		m_arrowPosition.x = 18.0f;
		m_arrowPosition.y = -6.0f;
		m_arrow.setScale(-1.0f, 1.0f);
		break;
	}

	m_arrow.setTextureRect(arrowRect);
}

void DialogueBox::SetNextArrow(bool next)
{
	if (next)
	{
		m_next.setTextureRect(sf::IntRect(9, 0, 9, 11));
	}
	else
	{
		m_next.setTextureRect(sf::IntRect(0, 0, 9, 11));
	}
}