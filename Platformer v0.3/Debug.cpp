#include "Debug.h"

std::vector<sf::RectangleShape> Debug::rects = {};
std::vector<std::array<sf::Vertex, 2>> Debug::lines = {};
HANDLE Debug::handle = GetStdHandle(STD_OUTPUT_HANDLE);


void Debug::Draw(Window* window)
{
	for (auto& r : rects)
	{
		window->Draw(r);
	}
	rects.clear();

	for (auto& l : lines)
	{
		sf::Vertex line[2] = { l.at(0), l.at(1) };
		window->Draw(line, 2, sf::Lines);
	}
	lines.clear();
}

void Debug::DrawCollider(const sf::Vector2f center, sf::Vector2u size, sf::Color colour)
{
	DrawRect(center, size, colour);
}

void Debug::DrawRect(const sf::Vector2f center, sf::Vector2u size, sf::Color colour)
{
	sf::Vector2f shapeSize(size.x, size.y);
	sf::RectangleShape shape(shapeSize);
	shape.setPosition(center);
	shape.setOutlineColor(colour);
	shape.setOutlineThickness(2.f);
	shape.setFillColor(sf::Color::Transparent);
	rects.push_back(shape);
}

void Debug::DrawRect(const sf::FloatRect& rect, sf::Color colour)
{
	sf::Vector2f size(rect.width, rect.height);
	sf::Vector2f pos(rect.left, rect.top);
	sf::RectangleShape shape(size);
	shape.setPosition(pos);
	shape.setOutlineColor(colour);
	shape.setOutlineThickness(2.f);
	shape.setFillColor(sf::Color::Transparent);
	rects.push_back(shape);
}

void Debug::DrawLine(const sf::Vector2f& from, const sf::Vector2f to, sf::Color colour)
{
	lines.push_back({ sf::Vertex(from, colour), sf::Vertex(to, colour) });
}

void Debug::Log(const std::string& msg)
{
	std::cout << "LOG: " << msg << "\n";
}

void Debug::Log(const std::string& msg, const std::string& from)
{
	std::cout << std::setiosflags(std::ios::left) << std::setw(DEBUG_LEFT_SIZE) << from << std::setiosflags(std::ios::left) << std::setw(DEBUG_TYPE_SIZE) << " LOG: " << msg << "\n";
}

void Debug::Log(const sf::Vector2f vector)
{
	std::cout << "LOG: (" << vector.x << " ; " << vector.y << ")\n";
}

void Debug::Log(const b2Vec2 vector)
{
	std::cout << "LOG: (" << vector.x << " ; " << vector.y << ")\n";
}

void Debug::LogInfo(const std::string& msg)
{
	SetConsoleTextAttribute(handle, (int)ConsoleColor::CYAN);
	std::cout << "INFO: " << msg << "\n";
	SetConsoleTextAttribute(handle, (int)ConsoleColor::WHITE);
}

void Debug::LogInfo(const std::string& msg, const std::string& from)
{
	SetConsoleTextAttribute(handle, (int)ConsoleColor::CYAN);
	std::cout << std::setiosflags(std::ios::left) << std::setw(DEBUG_LEFT_SIZE) << from << std::setiosflags(std::ios::left) << std::setw(DEBUG_TYPE_SIZE) << " INFO: " << msg << "\n";
	SetConsoleTextAttribute(handle, (int)ConsoleColor::WHITE);
}

void Debug::LogWarning(const std::string& msg)
{
	SetConsoleTextAttribute(handle, (int)ConsoleColor::YELLOW);
	std::cout << "WARNING: " << msg << "\n";
	SetConsoleTextAttribute(handle, (int)ConsoleColor::WHITE);
}

void Debug::LogWarning(const std::string& msg, const std::string& from)
{
	SetConsoleTextAttribute(handle, (int)ConsoleColor::YELLOW);
	std::cout << std::setiosflags(std::ios::left) << std::setw(DEBUG_LEFT_SIZE) << from << std::setiosflags(std::ios::left) << std::setw(DEBUG_TYPE_SIZE) << " WARNING: " << msg << "\n";
	SetConsoleTextAttribute(handle, (int)ConsoleColor::WHITE);
}

void Debug::LogError(const std::string& msg)
{
	SetConsoleTextAttribute(handle, (int)ConsoleColor::RED);
	std::cout << "ERROR: " << msg << "\n";
	SetConsoleTextAttribute(handle, (int)ConsoleColor::WHITE);
}

void Debug::LogError(const std::string& msg, const std::string& from)
{
	SetConsoleTextAttribute(handle, (int)ConsoleColor::RED);
	std::cout << std::setiosflags(std::ios::left) << std::setw(DEBUG_LEFT_SIZE) << from << std::setiosflags(std::ios::left) << std::setw(DEBUG_TYPE_SIZE) << " ERROR: " << msg << "\n";
	SetConsoleTextAttribute(handle, (int)ConsoleColor::WHITE);
}