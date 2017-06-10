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
	std::vector<sf::Text> m_buttons;

	sf::Font m_font;

	int m_currentButtonIndex;
};

