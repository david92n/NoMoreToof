#include "Game.h"



Game::Game(const std::string& title)
{
	m_window = new sf::RenderWindow(sf::VideoMode(384, 216), title, sf::Style::Titlebar | sf::Style::Close);

	m_player = new Player();
}


Game::~Game()
{
	delete m_window;
	delete m_player;
}

void Game::Run()
{
	while (m_window->isOpen())
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window->close();
		}

		m_window->clear();
		
		m_player->Render(*m_window);

		m_window->display();
	}
}
