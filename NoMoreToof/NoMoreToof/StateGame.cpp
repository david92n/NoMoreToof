#include "StateGame.h"
#include "Player.h"
#include "StateHandler.h"
#include "ResourceHandler.h"
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;


StateGame::StateGame() : m_currentRoom("room0"), m_isChangingRoom(false)
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
				m_rooms[roomid] = new Room(roomid);
			}
		}
		
		for (auto& room : rooms)
		{
			
			Room* main;
			Room* left;
			Room* right;
			Room* up;
			Room* down;
			
			if (room.find("id") != room.end())
			{
				std::string roomid = room["id"];
				main = m_rooms[roomid];
			}
			if (room.find("left") != room.end())
				left = m_rooms["left"];
			if (room.find("right") != room.end())
				right = m_rooms["right"];
			if (room.find("up") != room.end())
				up = m_rooms["up"];
			if (room.find("down") != room.end())
				down = m_rooms["down"];
				
			main->SetRooms(left, right, up, down);
		}
		
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

	m_player->PollEvent(e);
}

void StateGame::Update(float deltaTime)
{
	m_rooms[m_currentRoom]->Update(deltaTime);
	m_player->Update(deltaTime);
}

void StateGame::Render(sf::RenderTarget& renderTarget)
{
	m_rooms[m_currentRoom]->Render(renderTarget);
	m_player->Render(renderTarget);
}

void StateGame::TryEnterRoom(StateGame::Direction dir)
{
	std::cout << "Try enter room\n";

	Room* currentRoom = m_rooms[m_currentRoom];
}