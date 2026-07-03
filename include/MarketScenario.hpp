#pragma once

#include "Instrument.hpp"
#include "Portfolio.hpp"
#include <unordered_map>
#include <random>

class Portfolio;

class MarketScenario {
private:
    std::unordered_map<std::shared_ptr<Instrument>, double> scenario_state;
public:
    // create a market scenario by generating random values for each instrument in the portfolio
    MarketScenario(std::mt19937& rng, const Portfolio& portfolio) {
        for (auto& pair : portfolio.get_instruments()) {
            std::normal_distribution<double> dist(0, 1);
            scenario_state[pair.first] = dist(rng);
        }
    }
    const std::unordered_map<std::shared_ptr<Instrument>, double> get_scenario() const;
    ~MarketScenario() = default;
};