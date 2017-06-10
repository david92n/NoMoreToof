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

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position);

	sf::Vector2f GetStartPosition();
	void SetStartPosition(sf::Vector2f position);

	sf::Vector2f GetTargetPosition();
	void SetTargetPosition(sf::Vector2f position);

	void SetRooms(Room* left, Room* right, Room* up, Room* down);

	Room* GetLeftRoom();
	Room* GetRightRoom();
	Room* GetUpRoom();
	Room* GetDownRoom();
private:
	sf::Vector2f m_startPosition;
	sf::Vector2f m_targetPosition;

	sf::Vector2f m_position;
	sf::Sprite m_background;

	Room* m_left;
	Room* m_right;
	Room* m_up;
	Room* m_down;
};

