#include "Game.h"

Game::Game(const std::string& title)
{
	m_window = new sf::RenderWindow(sf::VideoMode(384*3, 216*3), title, sf::Style::Titlebar | sf::Style::Close);
	sf::FloatRect area(0.0f, 0.0f, 384.0f, 216.0f);
	m_window->setView(sf::View(area));

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
		sf::Time elapsed = m_clock.restart();

		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window->close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					m_window->close();
			}
		}

		m_window->clear();
		
		m_player->Update(elapsed.asSeconds());
		m_player->Render(*m_window);

		m_window->display();
	}
}
