#include "Window.h"

Window::Window(const std::string& windowName) : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), windowName, sf::Style::Close | sf::Style::Titlebar)
//Window::Window(const std::string& windowName) : window(sf::VideoMode(1920, 1080), windowName, sf::Style::Close | sf::Style::Titlebar)
{

}

void Window::Update()
{
	sf::Event event;
	if (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void Window::BeginDraw()
{
	window.clear(sf::Color::Black);
}

void Window::Draw(const sf::Drawable& drawable)
{
	window.draw(drawable);
}

void Window::Draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type)
{
	window.draw(vertices, vertexCount, type);
}

void Window::EndDraw()
{
	window.display();
}

sf::Vector2u Window::GetCentre() const
{
	sf::Vector2u size = window.getSize();

	return sf::Vector2u(size.x / 2, size.y / 2);
}

const sf::View& Window::GetView() const
{
	return window.getView();
}

void Window::SetView(const sf::View& view)
{
	window.setView(view);
}

bool Window::IsOpen()
{
	return window.isOpen();
}
