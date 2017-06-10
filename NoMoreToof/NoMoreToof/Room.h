#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <string>
class Room
{
public:
	Room(const std::string& roomName);
	~Room();

	void Update(float deltaTime);
	void Render(sf::RenderTarget& renderTarget);
private:
	sf::Sprite m_background;
};

