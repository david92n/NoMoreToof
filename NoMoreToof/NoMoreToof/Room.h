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

	void SetRooms(Room* left, Room* right, Room* up, Room* down);
private:
	sf::Sprite m_background;

	Room* m_left;
	Room* m_right;
	Room* m_up;
	Room* m_down;
};

