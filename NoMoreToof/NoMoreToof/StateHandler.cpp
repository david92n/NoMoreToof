#include "StateHandler.h"

std::stack<State*> StateHandler::_states;

void StateHandler::Push(State* state)
{
	_states.push(state);
}

void StateHandler::Pop()
{
	if (_states.size() < 1) return;

	delete _states.top();
	_states.pop();
}

void StateHandler::PollEvent(sf::Event& e)
{
	if (_states.size() > 0)
		_states.top()->PollEvent(e);
}

void StateHandler::Update(float deltaTime)
{
	if (_states.size() > 0)
		_states.top()->Update(deltaTime);
}

void StateHandler::Render(sf::RenderTarget& renderTarget)
{
	if (_states.size() > 0)
		_states.top()->Render(renderTarget);
}

size_t StateHandler::Size()
{
	return _states.size();
}
