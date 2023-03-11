#pragma once

#include <string>

#include "SFML/Graphics.hpp"

#include "AssetAllocator.h"
#include "Entity.h"

class Entity;

class Window
{
public:
	Window(const std::string& windowName);

	void Update();

	void BeginDraw();
	void Draw(const sf::Drawable& drawable);
	void Draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type);
	void Draw(sf::CircleShape shape);
	void Draw(Entity* entity);
	//TODO по необходимости добавить различные способы отрисовки
	void EndDraw();

	sf::Vector2u GetCentre() const;
	const sf::View& GetView() const;
	void SetView(const sf::View& view);

	bool IsOpen();

private:
	sf::RenderWindow window;

};