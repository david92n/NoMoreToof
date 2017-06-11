#include "Game.h"
#include "StateMenu.h"
#include "StateGame.h"
#include "StateHandler.h"
#include "ResourceHandler.h"

Game::Game(const std::string& title) : m_title(title), m_fullscreen(false)
{
	m_window = new sf::RenderWindow();
	CreateWindow(m_fullscreen);

	ResourceHandler::LoadDialogue();
}

Game::~Game()
{
	delete m_window;
}

void Game::Run()
{
	StateHandler::Push(new StateMenu());
	// DEBUG
	//StateHandler::Push(new StateGame());

	while (m_window->isOpen() && StateHandler::Size() > 0)
	{
		sf::Time elapsed = m_clock.restart();

		sf::Event event;
		while (m_window->pollEvent(event))
		{
			StateHandler::PollEvent(event);

			if (event.type == sf::Event::Closed)
			{
				m_window->close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					if(StateHandler::Size() < 1) m_window->close();
					break;
				case sf::Keyboard::F1:
					m_fullscreen = !m_fullscreen;
					CreateWindow(m_fullscreen);
					break;
				case sf::Keyboard::Up:
					//text.setCharacterSize(text.getCharacterSize() + 12);
					//text.move(0, -0.5);
					break;
				case sf::Keyboard::Down:
					//text.setCharacterSize(text.getCharacterSize() - 1);
					//text.move(0, 1);
					break;
				}	
			}
		}

		m_window->clear();
		
		StateHandler::Update(elapsed.asSeconds());
		StateHandler::Render(*m_window);

		m_window->display();
	}
}

void Game::CreateWindow(bool fullscreen)
{
	if (fullscreen)
	{
		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
		m_window->create(desktop, m_title, sf::Style::Fullscreen);
	}
	else
	{
		m_window->create(sf::VideoMode(384 * 3, 216 * 3), m_title, sf::Style::Titlebar | sf::Style::Close);
	}

	sf::FloatRect area(0.0f, 0.0f, 384.0f, 216.0f);
	m_window->setView(sf::View(area));

	m_window->setVerticalSyncEnabled(true);
}
