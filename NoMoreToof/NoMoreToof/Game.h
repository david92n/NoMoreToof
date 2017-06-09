#pragma once

#include "Player.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(const std::string& title);
	~Game();

	void Run();

private:
	sf::RenderWindow* m_window;
	
	Player* m_player;
};

