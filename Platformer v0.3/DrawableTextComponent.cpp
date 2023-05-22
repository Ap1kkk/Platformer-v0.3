#include "DrawableTextComponent.h"

void DrawableTextComponent::SetText(std::string string)
{
	text.setString(string);
	text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height);
}
