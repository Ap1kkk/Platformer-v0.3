#pragma once

#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"

#include "Window.h"
#include "DataTypes.h"

const float DEBUG_OUTLINE_THICKNESS = -2.f;
const unsigned char DEBUG_OUTLINE_COLOR_ALPHA = 220;
const unsigned char DEBUG_FILL_COLOR_ALPHA = 160;

class PhysicsDebugDraw : public b2Draw
{
public:
    PhysicsDebugDraw(Window* window) : window(window) {}
    ~PhysicsDebugDraw() {}

    // Переводит цвет с box2d для SFML
    sf::Color B2SFColor(const b2Color& color, int alpha);

    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    void DrawCircle(const b2Vec2& center, float radius, const b2Color& color);
    void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color);
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    void DrawTransform(const b2Transform& xf) {}
    void DrawPoint(const b2Vec2& p, float size, const b2Color& color);

private:
    Window* window;
};

