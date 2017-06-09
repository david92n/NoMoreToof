#include "EntityStatic.h"



EntityStatic::EntityStatic() : Entity("res/test")
{
}


EntityStatic::~EntityStatic()
{
}

void EntityStatic::Update(float deltaTime)
{

}

void EntityStatic::Render(sf::RenderTarget& renderTarget)
{
	Entity::Render(renderTarget);
}