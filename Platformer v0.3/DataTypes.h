#pragma once

#include <string>

#include "box2d/box2d.h"

typedef unsigned int EntityId;
typedef unsigned int ComponentId;
typedef unsigned int ComponentLayer;
typedef unsigned int SceneId;
typedef unsigned int TileId;
typedef unsigned int TileSetId;
typedef unsigned int SensorId;
typedef unsigned int FixtureId;

typedef std::string ComponentType;
typedef std::string Filename;

// 1 meter (box2d) is more or less 64 pixels (sfml)
#define RATIO 30.0f
#define PIXELS_PER_METER RATIO

// 64 pixels (sfml) are more or less 1 meter (box2d)
#define UNRATIO (1.0F/RATIO)
#define METERS_PER_PIXEL UNRATIO

//formula to convert radians to degrees = (radians * (pi/180))
#define RADTODEG (180.f / b2_pi)
