#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(const std::string& title);
	~Game();

	void Run();

private:
	void CreateWindow(bool fullscreen);

	std::string m_title;
	sf::RenderWindow* m_window;
	sf::Clock m_clock;

	bool m_fullscreen;
};

