#pragma once
#include "State.h"
#include "Room.h"
#include <map>

class Player;

class StateGame :
	public State
{
public:
	enum Direction { LEFT, RIGHT, UP, DOWN };

	StateGame();
	~StateGame();

	void PollEvent(sf::Event& e);
	void Update(float deltaTime);
	void Render(sf::RenderTarget& renderTarget);

	void TryEnterRoom(Direction dir);

private:
	Player* m_player;

	Room* m_currentRoom;
	Room* m_nextRoom;
	std::map<std::string, Room*> m_rooms;

	float m_timer;
	bool m_isChangingRoom;
};