#include "StateGame.h"
#include "StateHandler.h"

#include "ResourceHandler.h"

StateGame::StateGame()
{
	m_player = new Player();
	m_background.setTexture(*ResourceHandler::LoadTexture("res/background.png"));
}

StateGame::~StateGame()
{
	delete m_player;
}

void StateGame::PollEvent(sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		switch (e.key.code)
		{
		case sf::Keyboard::Escape:
			StateHandler::Pop();
			break;
		}
	}
}

void StateGame::Update(float deltaTime)
{
	m_player->Update(deltaTime);
}

void StateGame::Render(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(m_background);

	m_player->Render(renderTarget);
}