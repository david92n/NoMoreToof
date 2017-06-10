#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
class State
{
public:
	State();
	virtual ~State();

	virtual void PollEvent(sf::Event& e) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderTarget& renderTarget) = 0;
};

