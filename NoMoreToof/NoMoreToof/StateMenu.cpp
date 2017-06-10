#include "StateMenu.h"
#include "StateHandler.h"
#include "StateGame.h"
#include "ResourceHandler.h"

StateMenu::StateMenu() : State(), m_currentButtonIndex(0)
{
	sf::Font& font = *ResourceHandler::LoadFont("res/manaspc.ttf");

	m_buttons.resize(2);
	size_t size = m_buttons.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_buttons[i].setFont(font);
		m_buttons[i].setCharacterSize(12u);
	}

	m_buttons[0].setString("Play!");
	m_buttons[0].setPosition(10, 20);

	m_buttons[1].setString("Exit!");
	m_buttons[1].setPosition(10, 40);
}

StateMenu::~StateMenu()
{
}

void StateMenu::PollEvent(sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		switch (e.key.code)
		{
		case sf::Keyboard::Escape:
			StateHandler::Pop();
			break;
		case sf::Keyboard::Return:
			switch (m_currentButtonIndex)
			{
			case 0:
				StateHandler::Push(new StateGame());
				break;
			case 1:
				StateHandler::Pop();
				break;
			}
			
			break;
		case sf::Keyboard::Up:
			if (m_currentButtonIndex > 0)
				m_currentButtonIndex--;
			break;
		case sf::Keyboard::Down:
			if (m_currentButtonIndex < 1)
				m_currentButtonIndex++;
			break;
		}
	}
}

void StateMenu::Update(float deltaTime)
{

}

void StateMenu::Render(sf::RenderTarget& renderTarget)
{
	size_t size = m_buttons.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (m_currentButtonIndex == i)
		{
			m_buttons[i].setColor(sf::Color::Yellow);
		}
		else
		{
			m_buttons[i].setColor(sf::Color::White);
		}
		renderTarget.draw(m_buttons[i]);
	}
}
