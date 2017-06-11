#pragma once
#include "Entity.h"
#include "OneAnimation.h"
#include "TalkInfo.h"
#include "DialogueBox.h"

class EntityNPC :
	public Entity
{
public:
	EntityNPC(const std::string& texturePath, sf::Vector2f position, sf::Vector2f shadowOffset, int animRows, int animCols, int numFrames, float frameTime);
	~EntityNPC();

	void PollEvent(sf::Event& e);
	void Update(float deltaTime);
	void Render(sf::RenderTarget& renderTarget);

	std::vector<TalkInfo> GetTalkInfo();
	void SetTalkInfo(std::vector<TalkInfo> list);

	void UpdateDialogueBox();
private:
	OneAnimation m_animIdle;

	std::vector<TalkInfo> m_talkInfoList;

	DialogueBox m_dialogue;
};

