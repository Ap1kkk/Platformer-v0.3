#pragma once

#include "DataTypes.h"

class ISensor
{
public:
	ISensor() : sensorId(staticIdCounter++) {}

	SensorId GetSensorId() const { return sensorId; }

protected:
	SensorId sensorId;

private:
	static SensorId staticIdCounter;
};

