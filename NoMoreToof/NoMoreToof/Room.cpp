#include "Room.h"
#include "ResourceHandler.h"
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;

Room::Room(const std::string& roomName)
{
	std::ifstream i("res/rooms/" + roomName + ".json");
	json j;
	i >> j;

	if (j.find("background") != j.end())
	{
		std::string backgroundTexture = j["background"];
		m_background.setTexture(*ResourceHandler::LoadTexture(backgroundTexture));
	}
}

Room::~Room()
{
}

void Room::Update(float deltaTime)
{

}

void Room::Render(sf::RenderTarget& renderTarget)
{
	sf::Vector2f pixelPerfectPos(round(m_position.x), round(m_position.y));
	m_background.setPosition(pixelPerfectPos);
	renderTarget.draw(m_background);
}

sf::Vector2f Room::GetPosition()
{
	return m_position;
}

void Room::SetPosition(sf::Vector2f position)
{
	m_position = position;
}

sf::Vector2f Room::GetStartPosition()
{
	return m_startPosition;
}

void Room::SetStartPosition(sf::Vector2f position)
{
	m_startPosition = position;
}

sf::Vector2f Room::GetTargetPosition()
{
	return m_targetPosition;
}

void Room::SetTargetPosition(sf::Vector2f position)
{
	m_targetPosition = position;
}

void Room::SetRooms(Room* left, Room* right, Room* up, Room* down)
{
	m_left = left;
	m_right = right;
	m_up = up;
	m_down = down;
}

Room* Room::GetLeftRoom()
{
	return m_left;
}

Room* Room::GetRightRoom()
{
	return m_right;
}

Room* Room::GetUpRoom()
{
	return m_up;
}

Room* Room::GetDownRoom()
{
	return m_down;
}
