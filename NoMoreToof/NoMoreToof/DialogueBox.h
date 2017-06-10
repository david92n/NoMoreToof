#pragma once
#include <SFML/Graphics/Sprite.hpp>
class DialogueBox
{
public:
	enum Placement{ UPPERLEFT, UPPERRIGHT, LOWERLEFT, LOWERRIGHT };

	DialogueBox();
	~DialogueBox();

	bool GetActive();
	void SetActive(bool active);
	void SetLines();

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position);

	void Render(sf::RenderTarget& renderTarget);

	sf::Vector2u GetSpriteSize();

	void SetPlacementOffsets(sf::Vector2f offsets[4]);

	void SetOffsetLocation(Placement placementOffset);

private:
	sf::Sprite m_box;
	sf::Sprite m_arrow;
	sf::Sprite m_next;

	sf::Vector2f m_position;
	sf::Vector2f m_arrowPosition;
	bool m_active;

	Placement m_currentPlacementOffset;
	sf::Vector2f m_placementOffsets[4];
};

