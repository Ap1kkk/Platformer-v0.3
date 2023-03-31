#pragma once

#include "SFML/Graphics.hpp"
#include "Bitmask.h"

using Keyboard = sf::Keyboard;

class Input
{
public:
	enum class Key
	{
		None =			0,
		Left =			1,
		Right =			2,
		Up =			3,
		Down =			4,
		Horizontal =	5,
		Vertical =		6,
		Space =			7,
		Esc =			8,
		LBracket =		9,
		RBracket =		10,
		LShift =		11,
		RShift =		12,
		Q =				13,
		W =				14,
		E =				15,
		R =				16,
		T =				17,
		Y =				18,
		U =				19,
		I =				20,
		O =				21,
		P =				22,
		A =				23,
		S =				24,
		D =				25,
		F =				26,
		G =				27,
		H =				28,
		J =				29,
		K =				30,
		L =				31,
		Z =				32,
		X =				33,
		C =				34,
		V =				35,
		B =				36,
		N =				37,
		M =				38,

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