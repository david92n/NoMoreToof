#include "Room.h"
#include "EntityNPC.h"
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
	if (j.find("npcs") != j.end())
	{
		json npcs = j["npcs"];

		for (auto& npc : npcs)
		{
			if (npc.find("texture") != npc.end())
			{
				std::string texture = npc["texture"];
				
				sf::Vector2f position;
				sf::Vector2f shadowOffset;
				int numRows = 1;
				int numCols = 1;
				int numFrames = 1;
				float frameTime = 0.1f;
				std::string dialogueId;

				if (npc.find("x") != npc.end())
					position.x = npc["x"];
				if (npc.find("y") != npc.end())
					position.y = npc["y"];
				if (npc.find("shadowX") != npc.end())
					shadowOffset.x = npc["shadowX"];
				if (npc.find("shadowY") != npc.end())
					shadowOffset.y = npc["shadowY"];
				if (npc.find("numRows") != npc.end())
					numRows = npc["numRows"];
				if (npc.find("numCols") != npc.end())
					numCols = npc["numCols"];
				if (npc.find("numFrames") != npc.end())
					numFrames = npc["numFrames"];
				if (npc.find("frameTime") != npc.end())
					frameTime = npc["frameTime"];
				if (npc.find("dialogue") != npc.end())
					dialogueId = npc["dialogue"].get<std::string>();

				std::vector<TalkInfo> talkInfoList = ResourceHandler::GetDialogue(dialogueId);

				EntityNPC* newNPC = new EntityNPC(texture, position, shadowOffset, numRows, numCols, numFrames, frameTime);

				newNPC->SetTalkInfo(talkInfoList);

				m_npcs.push_back(newNPC);
			}
		}
	}
}

Room::~Room()
{
	for (auto npc : m_npcs)
		delete npc;
	m_npcs.clear();
}

void Room::Update(float deltaTime)
{
	size_t size = m_npcs.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_npcs[i]->Update(deltaTime);
	}
}

void Room::Render(sf::RenderTarget& renderTarget)
{
	sf::Vector2f pixelPerfectPos(round(m_position.x), round(m_position.y));
	m_background.setPosition(pixelPerfectPos);
	renderTarget.draw(m_background);

	size_t size = m_npcs.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_npcs[i]->SetRootPosition(m_npcs[i]->GetPosition() + pixelPerfectPos);
		m_npcs[i]->Render(renderTarget);
	}
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

std::vector<EntityNPC*>& Room::GetNPCList()
{
	return m_npcs;
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
