#include "PhysicsDebugDraw.h"

sf::Color PhysicsDebugDraw::B2SFColor(const b2Color& color, int alpha)
{
    sf::Color result((sf::Uint8)(color.r * 255), (sf::Uint8)(color.g * 255), (sf::Uint8)(color.b * 255), (sf::Uint8)alpha);
    return result;
}

void PhysicsDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(vertexCount);
    for (int32 i = 0; i < vertexCount; i++)
    {
        b2Vec2 vertex = vertices[i];
        sf::Vector2f vertexSFML = { vertex.x, vertex.y };
        polygon.setPoint(i, vertexSFML);
    }
    polygon.setOutlineThickness(DEBUG_OUTLINE_THICKNESS);
    polygon.setOutlineColor(B2SFColor(color, DEBUG_OUTLINE_COLOR_ALPHA));
    polygon.setFillColor(B2SFColor(color, DEBUG_FILL_COLOR_ALPHA));
    window->Draw(polygon);
}

void PhysicsDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(vertexCount);
    for (int32 i = 0; i < vertexCount; i++)
    {
        b2Vec2 vertex = vertices[i];
        sf::Vector2f vertexSFML = { vertex.x * RATIO, vertex.y * RATIO };
        polygon.setPoint(i, vertexSFML);
    }
    polygon.setOutlineThickness(DEBUG_OUTLINE_THICKNESS);
    polygon.setOutlineColor(B2SFColor(color, DEBUG_OUTLINE_COLOR_ALPHA));
    polygon.setFillColor(B2SFColor(color, DEBUG_FILL_COLOR_ALPHA));
    window->Draw(polygon);
}

void PhysicsDebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
    sf::CircleShape circle(radius);
    circle.setPosition(center.x - radius, center.y - radius);
    circle.setOutlineThickness(DEBUG_OUTLINE_THICKNESS);
    circle.setOutlineColor(B2SFColor(color, DEBUG_OUTLINE_COLOR_ALPHA));
    circle.setFillColor(B2SFColor(color, DEBUG_FILL_COLOR_ALPHA));
    window->Draw(circle);
}

void PhysicsDebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
    sf::CircleShape circle(radius);
    circle.setPosition(center.x - radius, center.y - radius);
    circle.setOutlineThickness(DEBUG_OUTLINE_THICKNESS);
    circle.setOutlineColor(B2SFColor(color, DEBUG_OUTLINE_COLOR_ALPHA));
    circle.setFillColor(B2SFColor(color, DEBUG_FILL_COLOR_ALPHA));
    window->Draw(circle);
}

void PhysicsDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(p1.x, p1.y)),
        sf::Vertex(sf::Vector2f(p2.x, p2.y))
    };
    line->color = B2SFColor(color, DEBUG_OUTLINE_COLOR_ALPHA);
    window->Draw(line, 2, sf::Lines);
}

void PhysicsDebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
    sf::CircleShape circle(size);
    circle.setPosition(p.x - size, p.y - size);
    circle.setOutlineColor(B2SFColor(color, DEBUG_OUTLINE_COLOR_ALPHA));
    circle.setFillColor(B2SFColor(color, DEBUG_FILL_COLOR_ALPHA));
    window->Draw(circle);
}
