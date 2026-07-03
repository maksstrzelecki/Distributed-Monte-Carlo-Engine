#pragma once

#include <random>
#include "MarketScenario.hpp"

class Task {
public:
    MarketScenario scenario;
    bool done = false;
    Task(std::mt19937& rng, Portfolio& portfolio) : 
        scenario(MarketScenario(rng, portfolio)) {}
    ~Task() = default;
};