#pragma once

#include <string>

#include <box2d/box2d.h>
//#include <SFML/Graphics.hpp>

typedef unsigned int EntityId;
typedef unsigned int ComponentId;
typedef unsigned int ComponentLayer;
typedef int DrawLayer;
typedef unsigned int SceneId;
typedef unsigned int TileId;
typedef unsigned int TileSetId;
typedef unsigned int SensorId;
typedef unsigned int FixtureId;
typedef unsigned int ChunkId;

typedef std::string ComponentType;
typedef std::string Filename;

//#define WINDOW_WIDTH 1024
//#define WINDOW_HEIGHT 768
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define FIXED_DELTA_TIME 1.f / 45.f;

// 1 meter (box2d) is more or less 64 pixels (sfml)
#define RATIO 30.0f
#define PIXELS_PER_METER RATIO

// 64 pixels (sfml) are more or less 1 meter (box2d)
#define UNRATIO (1.0F/RATIO)
#define METERS_PER_PIXEL UNRATIO

//formula to convert radians to degrees = (radians * (pi/180))
#define RADTODEG (180.f / b2_pi)

enum class GameStateType
{
	Created = 0,
	Initialized,
	Runned,
	Paused,
	Exited
};

enum class CollisionLayers
{
	Default = 1,
	Ground,
	Player,
	Enemy,
	Projectile,
	Sensor,
	JumpSensor,
	AttackSensor 
};
