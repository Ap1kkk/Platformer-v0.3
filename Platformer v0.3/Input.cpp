#include "Input.h"


void Input::Update()
{
    lastFrameKeys.SetMask(thisFrameKeys);
    lastFrameInputAxes = inputAxes;

    float horizontal = (int)thisFrameKeys.GetBit((int)Key::Right) - (int)thisFrameKeys.GetBit((int)Key::Left);
    float vertical = (int)thisFrameKeys.GetBit((int)Key::Down) - (int)thisFrameKeys.GetBit((int)Key::Up);

    inputAxes.x = horizontal;
    inputAxes.y = vertical;


    thisFrameKeys.SetBit((int)Key::Left,
        (Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A)));

    thisFrameKeys.SetBit((int)Key::Right,
        (Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D)));

    thisFrameKeys.SetBit((int)Key::Up,
        (Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W)));

    thisFrameKeys.SetBit((int)Key::Down,
        (Keyboard::isKeyPressed(Keyboard::Down)) || (Keyboard::isKeyPressed(Keyboard::S)));

    thisFrameKeys.SetBit((int)Key::Horizontal,
        (thisFrameKeys.GetBit((int)Key::Left) || thisFrameKeys.GetBit((int)Key::Right)));

    thisFrameKeys.SetBit((int)Key::Vertical,
        (thisFrameKeys.GetBit((int)Key::Up) || thisFrameKeys.GetBit((int)Key::Down)));

    thisFrameKeys.SetBit((int)Key::Esc, Keyboard::isKeyPressed(Keyboard::Escape));

    thisFrameKeys.SetBit((int)Key::LBracket, Keyboard::isKeyPressed(Keyboard::LBracket));
    thisFrameKeys.SetBit((int)Key::RBracket, Keyboard::isKeyPressed(Keyboard::RBracket));

    thisFrameKeys.SetBit((int)Key::Space, Keyboard::isKeyPressed(Keyboard::Space));
    thisFrameKeys.SetBit((int)Key::LShift, Keyboard::isKeyPressed(Keyboard::LShift));
    thisFrameKeys.SetBit((int)Key::RShift, Keyboard::isKeyPressed(Keyboard::RShift));

    thisFrameKeys.SetBit((int)Key::LMouseButton, sf::Mouse::isButtonPressed(sf::Mouse::Left));
    thisFrameKeys.SetBit((int)Key::RMouseButton, sf::Mouse::isButtonPressed(sf::Mouse::Right));

    thisFrameKeys.SetBit((int)Key::Q, Keyboard::isKeyPressed(Keyboard::Q));
    thisFrameKeys.SetBit((int)Key::W, Keyboard::isKeyPressed(Keyboard::W));
    thisFrameKeys.SetBit((int)Key::E, Keyboard::isKeyPressed(Keyboard::E));
    thisFrameKeys.SetBit((int)Key::R, Keyboard::isKeyPressed(Keyboard::R));
    thisFrameKeys.SetBit((int)Key::T, Keyboard::isKeyPressed(Keyboard::T));
    thisFrameKeys.SetBit((int)Key::Y, Keyboard::isKeyPressed(Keyboard::Y));
    thisFrameKeys.SetBit((int)Key::U, Keyboard::isKeyPressed(Keyboard::U));
    thisFrameKeys.SetBit((int)Key::I, Keyboard::isKeyPressed(Keyboard::I));
    thisFrameKeys.SetBit((int)Key::O, Keyboard::isKeyPressed(Keyboard::O));
    thisFrameKeys.SetBit((int)Key::P, Keyboard::isKeyPressed(Keyboard::P));
    thisFrameKeys.SetBit((int)Key::A, Keyboard::isKeyPressed(Keyboard::A));
    thisFrameKeys.SetBit((int)Key::S, Keyboard::isKeyPressed(Keyboard::S));
    thisFrameKeys.SetBit((int)Key::D, Keyboard::isKeyPressed(Keyboard::D));
    thisFrameKeys.SetBit((int)Key::F, Keyboard::isKeyPressed(Keyboard::F));
    thisFrameKeys.SetBit((int)Key::G, Keyboard::isKeyPressed(Keyboard::G));
    thisFrameKeys.SetBit((int)Key::H, Keyboard::isKeyPressed(Keyboard::H));
    thisFrameKeys.SetBit((int)Key::J, Keyboard::isKeyPressed(Keyboard::J));
    thisFrameKeys.SetBit((int)Key::K, Keyboard::isKeyPressed(Keyboard::K));
    thisFrameKeys.SetBit((int)Key::L, Keyboard::isKeyPressed(Keyboard::L));
    thisFrameKeys.SetBit((int)Key::Z, Keyboard::isKeyPressed(Keyboard::Z));
    thisFrameKeys.SetBit((int)Key::X, Keyboard::isKeyPressed(Keyboard::X));
    thisFrameKeys.SetBit((int)Key::C, Keyboard::isKeyPressed(Keyboard::C));
    thisFrameKeys.SetBit((int)Key::V, Keyboard::isKeyPressed(Keyboard::V));
    thisFrameKeys.SetBit((int)Key::B, Keyboard::isKeyPressed(Keyboard::B));
    thisFrameKeys.SetBit((int)Key::N, Keyboard::isKeyPressed(Keyboard::N));
    thisFrameKeys.SetBit((int)Key::M, Keyboard::isKeyPressed(Keyboard::M));

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

bool Input::IsInputAxesChanged()
{
    return inputAxes != lastFrameInputAxes;
}

bool Input::IsInputAxesEnabled()
{
    return inputAxes != sf::Vector2f(0.f, 0.f) && lastFrameInputAxes == sf::Vector2f(0.f, 0.f);
}

bool Input::IsInputAxesDisabled()
{
    return inputAxes == sf::Vector2f(0.f, 0.f) && lastFrameInputAxes != sf::Vector2f(0.f, 0.f);
}

Bitmask Input::thisFrameKeys;
Bitmask Input::lastFrameKeys;
sf::Vector2f Input::inputAxes;
sf::Vector2f Input::lastFrameInputAxes;
