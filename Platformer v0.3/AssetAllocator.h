#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <assert.h>
#include <string>
#include <map>

class AssetAllocator
{

public:
	AssetAllocator();

	static sf::Texture& GetTexture(std::string const& filename);
	static sf::Texture* GetTexturePtr(std::string const& filename);
	static sf::SoundBuffer& GetSoundBuffer(std::string const& filename);
	static sf::Font& GetFont(std::string const& filename);
	static std::string& GetPath();
private:

	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::SoundBuffer> soundBuffer;
	std::map<std::string, sf::Font> fonts;

	static std::string path;

	static AssetAllocator* sInstance;
};