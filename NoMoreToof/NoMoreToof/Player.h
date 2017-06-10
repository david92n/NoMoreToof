#pragma once
#include "Entity.h"
#include "SpriteAnimation.h"
#include "DialogueBox.h"

class StateGame;

class Player :
	public Entity
{
public:
	Player(StateGame* game);
	~Player();

	void PollEvent(sf::Event& e);
	virtual void Update(float deltaTime);
	virtual void Render(sf::RenderTarget& renderTarget);
private:
	void HandleWallCollision();
	void UpdateDialogueBox();

	StateGame* m_game;

	SpriteAnimation m_animIdle;
	SpriteAnimation m_animWalk;

	DialogueBox m_dialogue;

	bool m_isWalking;
};