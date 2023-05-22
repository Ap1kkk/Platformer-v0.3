#include "FixtureManager.h"

std::map<FixtureId, Fixture*> FixtureManager::fixtures = {};
std::vector<std::pair<Fixture*, b2Body*>> FixtureManager::destroyBuffer = {};
