#pragma once

#include "SFML/Graphics.hpp"
#include "Bitmask.h"

class Input
{
public:
	enum class Key
	{
		None = 0,
		Left = 1,
		Right = 2,
		Up = 3,
		Down = 4,
		Horizontal = 5,
		Vertical = 6,
		Space = 7,
		Esc = 8,
		LBracket = 9,
		RBracket = 10,
		E = 11,
		LShift = 12,
	};

	static void Update();

	static sf::Vector2f GetInputAxes();

	static bool IsKeyPressed(Key keycode);
	static bool IsKeyDown(Key keycode);
	static bool IsKeyUp(Key keycode);

private:
	static Bitmask thisFrameKeys;
	static Bitmask lastFrameKeys;
	static sf::Vector2f inputAxes;
};