#pragma once
#include "State.h"
#include "Room.h"
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
	Room m_room;
};

