#include "EntityNPC.h"

EntityNPC::EntityNPC(const std::string& texturePath, sf::Vector2f position, sf::Vector2f shadowOffset, int animRows, int animCols, int numFrames, float frameTime)
	: Entity("shadow"), m_animIdle(texturePath, animRows, animCols, numFrames, frameTime)
{
	m_spriteOffset.x = shadowOffset.x;
	m_spriteOffset.y = shadowOffset.y;

	m_position = position;

	sf::Vector2f offsets[4];

	offsets[0] = sf::Vector2f(0.0f - (float)(m_dialogue.GetSpriteSize().x - m_animIdle.GetSpriteSize().x), -80.0f);
	offsets[1] = sf::Vector2f(0.0f, -80.0f);
	offsets[2] = sf::Vector2f(0.0f - (float)(m_dialogue.GetSpriteSize().x - m_animIdle.GetSpriteSize().x), 40.0f);
	offsets[3] = sf::Vector2f(0.0f, 40.0f);

	m_dialogue.SetPlacementOffsets(offsets);
}

EntityNPC::~EntityNPC()
{
}

void EntityNPC::PollEvent(sf::Event& e)
{
	m_dialogue.PollEvent(e);
}

void EntityNPC::Update(float deltaTime)
{
	m_animIdle.Update(deltaTime);

	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		m_dialogue.SetActive(true);
	}
	*/

	UpdateDialogueBox();
	m_dialogue.Update(deltaTime);
}

void EntityNPC::Render(sf::RenderTarget& renderTarget)
{
	Entity::Render(renderTarget);

	m_animIdle.SetPosition(m_rootPosition + m_position);
	m_animIdle.Render(renderTarget);

	m_dialogue.Render(renderTarget);
}

std::vector<TalkInfo> EntityNPC::GetTalkInfo()
{
	return m_talkInfoList;
}

void EntityNPC::SetTalkInfo(std::vector<TalkInfo> list)
{
	m_talkInfoList = list;
}

void EntityNPC::UpdateDialogueBox()
{
	bool upper = !(m_position.y < (float)m_dialogue.GetSpriteSize().y);
	bool left = m_position.x >(float)(m_dialogue.GetSpriteSize().x - m_animIdle.GetSpriteSize().x);

	int placement = upper ? 0 : 2;
	if (!left) placement++;
	m_dialogue.SetOffsetLocation((DialogueBox::Placement)placement);

	m_dialogue.SetPosition(m_rootPosition + m_position);
}