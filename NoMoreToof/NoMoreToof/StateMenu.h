#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "State.h"
class StateMenu : public State
{
public:
	StateMenu();
	~StateMenu();

	virtual void PollEvent(sf::Event& e);
	virtual void Update(float deltaTime);
	virtual void Render(sf::RenderTarget& renderTarget);

private:
	sf::Sprite m_background;
	std::vector<sf::Text> m_buttons;

	int m_currentButtonIndex;
};

