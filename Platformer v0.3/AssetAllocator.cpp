#include "AssetAllocator.h"

AssetAllocator* AssetAllocator::sInstance = nullptr;
std::string AssetAllocator::path = "";

AssetAllocator::AssetAllocator()
{
	// Разрешить существование только одного AssetManager
	// В противном случае сгенерировать исключение
	assert(sInstance == nullptr);
	sInstance = this;
	path = "../Assets/";
}

sf::Texture& AssetAllocator::GetTexture(std::string const& filename)
{
	auto& textureMap = sInstance->textures;

	auto pairFound = textureMap.find(filename);

	if (pairFound != textureMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto& texture = textureMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}

sf::Texture* AssetAllocator::GetTexturePtr(std::string const& filename)
{
	auto& texMap = sInstance->textures;

	auto pairFound = texMap.find(filename);

	if (pairFound != texMap.end())
	{
		return &(pairFound->second);
	}
	else
	{
		auto& texture = texMap[filename];
		texture.loadFromFile(filename);
		return &texture;
	}
}

//sf::SoundBuffer& AssetAllocator::GetSoundBuffer(std::string const& filename)
//{
//	// TODO: вставьте здесь оператор return
//}
//
//sf::Font& AssetAllocator::GetFont(std::string const& filename)
//{
//	// TODO: вставьте здесь оператор return
//}

std::string& AssetAllocator::GetPath()
{
	return path;
}
