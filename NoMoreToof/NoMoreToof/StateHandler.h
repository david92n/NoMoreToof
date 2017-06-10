#pragma once
#include <stack>
#include "State.h"
class StateHandler
{
public:
	static void Push(State* state);
	static void Pop();

	static void PollEvent(sf::Event& e);
	static void Update(float deltaTime);
	static void Render(sf::RenderTarget& renderTarget);

	static size_t Size();
private:
	static std::stack<State*> _states;
};

