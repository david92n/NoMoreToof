#include "Player.h"



Player::Player() : Entity("res/test.png")
{
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{

}

void Player::Render(sf::RenderTarget& renderTarget)
{
	Entity::Render(renderTarget);
}
