#include "MarketScenario.hpp"

const std::unordered_map<std::shared_ptr<Instrument>, double> MarketScenario::get_scenario() const {
    return scenario_state;
}