#pragma once

#include <random>
#include <future>
#include "MarketScenario.hpp"

class Task {
public:
    MarketScenario scenario;
    bool done = false;

    std::promise<double> p;
    std::future<double> f = p.get_future();
    Task(std::mt19937& rng, Portfolio& portfolio) : scenario(MarketScenario(rng, portfolio)) {}
    ~Task() = default;
};