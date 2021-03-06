#include "StateGame.h"
#include "Player.h"
#include "EntityNPC.h"
#include "StateHandler.h"
#include "ResourceHandler.h"
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;

#include <iostream>

StateGame::StateGame() : m_isChangingRoom(false), m_timer(0.0f), m_currentTalkingNPC(nullptr)
{
	m_player = new Player(this);

	std::ifstream i("res/map.json");
	json j;
	i >> j;

	if (j.find("rooms") != j.end())
	{
		json rooms = j["rooms"];
		
		for (auto& room : rooms) 
		{
			if (room.find("id") != room.end())
			{
				std::string roomid = room["id"];
				Room* newRoom = new Room(roomid);
				m_rooms[roomid] = newRoom;
			}
		}
		
		for (auto& room : rooms)
		{
			
			Room* main = nullptr;
			Room* left = nullptr;
			Room* right = nullptr;
			Room* up = nullptr;
			Room* down = nullptr;
			
			if (room.find("id") != room.end())
			{
				std::string roomid = room["id"];
				main = m_rooms[roomid];
			}
			if (room.find("left") != room.end() && !room["left"].is_null())
				left = m_rooms[room["left"]];
			if (room.find("right") != room.end() && !room["right"].is_null())
				right = m_rooms[room["right"]];
			if (room.find("up") != room.end() && !room["up"].is_null())
				up = m_rooms[room["up"]];
			if (room.find("down") != room.end() && !room["down"].is_null())
				down = m_rooms[room["down"]];
				
			main->SetRooms(left, right, up, down);
		}
		
		m_currentRoom = m_rooms["room0"];
		//m_background.setTexture(*ResourceHandler::LoadTexture(backgroundTexture));
	}
}

StateGame::~StateGame()
{
	delete m_player;

	for (auto room : m_rooms)
		delete room.second;
	m_rooms.clear();
}

void StateGame::PollEvent(sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		switch (e.key.code)
		{
		case sf::Keyboard::Escape:
			StateHandler::Pop();
			return;
		}
	}
	if (!m_isChangingRoom)
	{
		m_player->PollEvent(e);

		if (m_currentTalkingNPC != nullptr)
			m_currentTalkingNPC->PollEvent(e);
	}	
}

sf::Vector2f lerp(float t, sf::Vector2f a, sf::Vector2f b)
{
	return (1 - t)*a + t*b;
}

void StateGame::Update(float deltaTime)
{
	if (m_isChangingRoom)
	{
		m_timer += deltaTime;
		if (m_timer >= 1.0f)
		{
			m_timer = 1.0f;
			m_isChangingRoom = false;
		}
		m_currentRoom->SetPosition(lerp(m_timer, m_currentRoom->GetStartPosition(), m_currentRoom->GetTargetPosition()));
		m_nextRoom->SetPosition(lerp(m_timer, m_nextRoom->GetStartPosition(), m_nextRoom->GetTargetPosition()));

		m_player->SetPosition(lerp(m_timer, m_player->GetStartPosition(), m_player->GetTargetPosition()));

		if (!m_isChangingRoom)
		{
			m_currentRoom = m_nextRoom;
			m_nextRoom = nullptr;
		}
	}
	else
	{
		m_currentRoom->Update(deltaTime);
		m_player->Update(deltaTime);

		//CheckForDialogue();
	}
}

void StateGame::Render(sf::RenderTarget& renderTarget)
{
	if (m_isChangingRoom)
	{
		m_nextRoom->Render(renderTarget);
	}

	m_currentRoom->Render(renderTarget);
	
	m_player->Render(renderTarget);
}

void StateGame::TryEnterRoom(StateGame::Direction dir)
{
	if (m_isChangingRoom) return;

	Room* currentRoom = m_currentRoom;

	sf::Vector2f newRoomPosition;
	sf::Vector2f oldRoomTarget;
	sf::Vector2f playerOffset;

	Room* newRoom;

	switch (dir)
	{
	case StateGame::Direction::LEFT:
		newRoom = currentRoom->GetLeftRoom();
		newRoomPosition.x = -384.0f;
		oldRoomTarget.x = 384.0f;
		playerOffset.x = 352.0f;
		break;
	case StateGame::Direction::RIGHT:
		newRoom = currentRoom->GetRightRoom();
		newRoomPosition.x = 384.0f;
		oldRoomTarget.x = -384.0f;
		playerOffset.x = -352.0f;
		break;
	case StateGame::Direction::UP:
		newRoom = currentRoom->GetUpRoom();
		newRoomPosition.y = -216.0f;
		oldRoomTarget.y = 216.0f;
		playerOffset.y = 182;
		break;
	case StateGame::Direction::DOWN:
		newRoom = currentRoom->GetDownRoom();
		newRoomPosition.y = 216.0f;
		oldRoomTarget.y = -216.0f;
		playerOffset.y = -182;
		break;
	}

	if (newRoom == nullptr) return;

	newRoom->SetPosition(newRoomPosition);
	newRoom->SetStartPosition(newRoomPosition);
	newRoom->SetTargetPosition(sf::Vector2f(0.0f, 0.0f));
	
	currentRoom->SetStartPosition(sf::Vector2f(0.0f, 0.0f));
	currentRoom->SetTargetPosition(oldRoomTarget);

	m_player->SetStartPosition(m_player->GetPosition());
	m_player->SetTargetPosition(m_player->GetPosition() + playerOffset);

	m_isChangingRoom = true;
	m_nextRoom = newRoom;
	m_timer = 0.0f;
}

void StateGame::CheckForDialogue()
{
	std::vector<EntityNPC*>& npcList = m_currentRoom->GetNPCList();

	sf::Vector2f playerPos = m_player->GetSpritePosition();

	size_t size = npcList.size();
	for (size_t i = 0; i < size; ++i)
	{
		sf::Vector2f npcPos = npcList[i]->GetSpritePosition();
		
		sf::Vector2f delta = npcPos - playerPos;

		float sqrLength = delta.x * delta.x + delta.y * delta.y;

		if (sqrLength < 2500)
		{
			//std::cout << "close to npc: " << i << "\n";
			m_currentTalkingNPC = npcList[i];
		}
	}
}