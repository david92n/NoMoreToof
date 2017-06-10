#include "StateGame.h"
#include "StateHandler.h"

#include "ResourceHandler.h"

StateGame::StateGame() : m_room("room0")
{
	m_player = new Player();
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
			return;
		}
	}

	m_player->PollEvent(e);
}

void StateGame::Update(float deltaTime)
{
	m_room.Update(deltaTime);
	m_player->Update(deltaTime);
}

void StateGame::Render(sf::RenderTarget& renderTarget)
{
	m_room.Render(renderTarget);
	m_player->Render(renderTarget);
}