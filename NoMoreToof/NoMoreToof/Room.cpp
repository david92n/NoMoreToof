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
	renderTarget.draw(m_background);
}

void Room::SetRooms(Room* left, Room* right, Room* up, Room* down)
{
	m_left = left;
	m_right = right;
	m_up = up;
	m_down = down;
}
