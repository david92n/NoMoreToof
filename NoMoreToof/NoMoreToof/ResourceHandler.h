#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "TalkInfo.h"

class ResourceHandler
{
public:
	static sf::Texture* LoadTexture(const std::string& path);
	static void UnloadTexture(const std::string& path);
	static void UnloadAllTextures();

	static sf::Font* LoadFont(const std::string& path);
	static void UnloadFont(const std::string& path);
	static void UnloadAllFonts();

	static void LoadDialogue();
	static std::vector<TalkInfo> GetDialogue(std::string talkId);
private:
	static std::map<std::string, sf::Texture*> _textures;
	static std::map<std::string, sf::Font*> _fonts;

	static std::map<std::string, std::vector<TalkInfo>> _dialogues;
};

