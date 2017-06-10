#pragma once
#include "State.h"

#include "Player.h"

class StateGame :
	public State
{
public:
	StateGame();
	~StateGame();

	void PollEvent(sf::Event& e);
	void Update(float deltaTime);
	void Render(sf::RenderTarget& renderTarget);

private:
	Player* m_player;

	sf::Sprite m_background;
	sf::Text m_text;
};

