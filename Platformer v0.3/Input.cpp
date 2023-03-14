#include "Input.h"


void Input::Update()
{
    lastFrameKeys.SetMask(thisFrameKeys);

    float horizontal = (int)thisFrameKeys.GetBit((int)Key::Right) - (int)thisFrameKeys.GetBit((int)Key::Left);
    float vertical = (int)thisFrameKeys.GetBit((int)Key::Down) - (int)thisFrameKeys.GetBit((int)Key::Up);

    inputAxes.x = horizontal;
    inputAxes.y = vertical;

    thisFrameKeys.SetBit((int)Key::Left,
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)));

    thisFrameKeys.SetBit((int)Key::Right,
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)));

    thisFrameKeys.SetBit((int)Key::Up,
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)));

    thisFrameKeys.SetBit((int)Key::Down,
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)));

    thisFrameKeys.SetBit((int)Key::Esc, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));

    thisFrameKeys.SetBit((int)Key::LBracket, sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket));
    thisFrameKeys.SetBit((int)Key::RBracket, sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket));

    thisFrameKeys.SetBit((int)Key::E, sf::Keyboard::isKeyPressed(sf::Keyboard::E));
}

sf::Vector2f Input::GetInputAxes()
{
    return inputAxes;
}

bool Input::IsKeyPressed(Key keycode)
{
    return thisFrameKeys.GetBit((int)keycode);
}

bool Input::IsKeyDown(Key keycode)
{
    bool lastFrame = lastFrameKeys.GetBit((int)keycode);
    bool thisFrame = thisFrameKeys.GetBit((int)keycode);

    return thisFrame && !lastFrame;
}

bool Input::IsKeyUp(Key keycode)
{
    bool lastFrame = lastFrameKeys.GetBit((int)keycode);
    bool thisFrame = thisFrameKeys.GetBit((int)keycode);

    return !thisFrame && lastFrame;
}

Bitmask Input::thisFrameKeys;
Bitmask Input::lastFrameKeys;
sf::Vector2f Input::inputAxes;