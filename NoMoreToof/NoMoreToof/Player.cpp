#include "Player.h"



Player::Player() : Entity("res/test.png"), m_animIdle("res/toofidle.png", 4, 6, 0.1f), m_animWalk("res/toofwalk.png", 4, 8, 0.06f), m_isWalking(false)
{
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	sf::Vector2f input;

	int animIndex = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		animIndex = 2;
		input.x += 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		animIndex = 3;
		input.x -= 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		animIndex = 0;
		input.y += 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		animIndex = 1;
		input.y -= 1.0f;
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
}

void Player::Render(sf::RenderTarget& renderTarget)
{
	if (m_isWalking)
	{
		m_animWalk.Render(renderTarget);
	}
	else
	{
		m_animIdle.Render(renderTarget);
	}
	
	//Entity::Render(renderTarget);
}
