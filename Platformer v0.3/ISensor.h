#pragma once

#include "DataTypes.h"

class ISensor
{
public:
	ISensor() : sensorId(staticIdCounter++) {}

	SensorId GetSensorId() const { return sensorId; }

protected:
	const SensorId sensorId;

private:
	static SensorId staticIdCounter;
};

