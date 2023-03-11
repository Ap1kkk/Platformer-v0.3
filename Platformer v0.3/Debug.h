#pragma once


#include <array>
#include <iostream>
#include <iomanip>
#include <string>
#include "SFML/Graphics.hpp"
#include <Windows.h>
#include "Window.h"

class Window;

enum class ConsoleColor
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	PURPLE = 5,
	YELLOW = 6,
	WHITE = 7,
	GREY = 8,
	LIGHT_BLUE = 9,
	LIGHT_CYAN = 10,
	LIGHT_RED = 11,
	LIGHT_PURPLE = 12,
	LIGHT_YELLOW = 13,
	BRIGHT_WHITE = 14
};
const int DEBUG_LEFT_SIZE = 25;
const int DEBUG_TYPE_SIZE = 10;

class Debug
{
public:
	static void Draw(Window* window);

	static void DrawCollider(const sf::Vector2f center, sf::Vector2u size, sf::Color colour = sf::Color::Green);

	static void DrawRect(const sf::Vector2f center, sf::Vector2u size, sf::Color colour = sf::Color::Green);
	static void DrawRect(const sf::FloatRect& rect, sf::Color colour = sf::Color::Green);
	static void DrawLine(const sf::Vector2f& from, const sf::Vector2f to, sf::Color colour = sf::Color::White);

	static void Log(const std::string& msg);
	static void Log(const std::string& msg, const std::string& from);
	static void LogWarning(const std::string& msg);
	static void LogWarning(const std::string& msg, const std::string& from);
	static void LogError(const std::string& msg);
	static void LogError(const std::string& msg, const std::string& from);

private:
	static std::vector<std::array<sf::Vertex, 2>> lines;
	static std::vector<sf::RectangleShape> rects;

	static HANDLE handle;
};

