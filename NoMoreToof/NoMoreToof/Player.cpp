#include "Player.h"
#include <iostream>

Player::Player() : Entity("shadow"), m_animIdle("toofidle", 4, 6, 0.1f), m_animWalk("toofwalk", 4, 8, 0.06f), m_isWalking(false)
{
	m_spriteOffset.x = 7;
	m_spriteOffset.y = 29;

	m_position.x = 50;
	m_position.y = 100;

	sf::Vector2f offsets[4];

	offsets[0] = sf::Vector2f(0.0f - (float)(m_dialogue.GetSpriteSize().x - m_animIdle.GetSpriteSize().x), -80.0f);
	offsets[1] = sf::Vector2f(0.0f, -80.0f);
	offsets[2] = sf::Vector2f(0.0f - (float)(m_dialogue.GetSpriteSize().x - m_animIdle.GetSpriteSize().x), 40.0f);
	offsets[3] = sf::Vector2f(0.0f, 40.0f);

	m_dialogue.SetPlacementOffsets(offsets);
}

Player::~Player()
{
}

void Player::PollEvent(sf::Event& e)
{
	m_dialogue.PollEvent(e);
	if (e.type == sf::Event::KeyPressed)
	{
		switch (e.key.code)
		{
		case sf::Keyboard::X:
			//m_dialogue.SetActive(!m_dialogue.GetActive());
			m_dialogue.SetActive(true);
			break;
		}
	}
}

void Player::Update(float deltaTime)
{
	sf::Vector2f input;

	int animIndex = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		animIndex = 2;
		input.x += 1.0f;
		//m_dialogue.SetOffsetLocation(DialogueBox::UPPERLEFT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		animIndex = 3;
		input.x -= 1.0f;
		//m_dialogue.SetOffsetLocation(DialogueBox::UPPERRIGHT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		animIndex = 0;
		input.y += 1.0f;
		//m_dialogue.SetOffsetLocation(DialogueBox::LOWERLEFT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		animIndex = 1;
		input.y -= 1.0f;
		//m_dialogue.SetOffsetLocation(DialogueBox::LOWERRIGHT);
	}

	if (input.x != 0.0f && input.y != 0.0f)
	{
		float len = sqrt(1.0f / (input.x * input.x + input.y * input.y));
		input *= len;
	}

	m_isWalking = input.x != 0.0f || input.y != 0.0f;

	m_position += input * 50.0f * deltaTime;
	m_animIdle.SetPosition(m_position);
	m_animWalk.SetPosition(m_position);

	if (animIndex != -1)
	{
		m_animIdle.SetAnimation(animIndex);
		m_animWalk.SetAnimation(animIndex);
	}
	
	m_animIdle.Update(deltaTime);
	m_animWalk.Update(deltaTime);

	UpdateDialogueBox();
	m_dialogue.Update(deltaTime);
}

void Player::Render(sf::RenderTarget& renderTarget)
{
	Entity::Render(renderTarget);

	if (m_isWalking)
	{
		m_animWalk.Render(renderTarget);
	}
	else
	{
		m_animIdle.Render(renderTarget);
	}

	m_dialogue.Render(renderTarget);
}

void Player::UpdateDialogueBox()
{
	bool upper = !(m_position.y < (float)m_dialogue.GetSpriteSize().y);
	bool left = m_position.x > (float)(m_dialogue.GetSpriteSize().x - m_animIdle.GetSpriteSize().x);
	
	int placement = upper ? 0 : 2;
	if (!left) placement++;
	m_dialogue.SetOffsetLocation((DialogueBox::Placement)placement);

	m_dialogue.SetPosition(m_position);
}
