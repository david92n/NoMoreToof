#include "StateGame.h"
#include "StateHandler.h"

#include "ResourceHandler.h"

StateGame::StateGame()
{
	m_player = new Player();
	m_background.setTexture(*ResourceHandler::LoadTexture("res/background.png"));

	m_text.setFont(*ResourceHandler::LoadFont("res/manaspc.ttf"));
	m_text.setCharacterSize(12u);
	m_text.setString("Yo this is a sample text, what do you think?\nnew line?");
	m_text.setPosition(10, 50);
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
	m_player->Update(deltaTime);
}

void StateGame::Render(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(m_background);

	m_player->Render(renderTarget);

	//renderTarget.draw(m_text);
}