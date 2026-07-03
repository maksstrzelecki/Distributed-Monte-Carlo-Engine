#include "Portfolio.hpp"
#include "MarketScenario.hpp"

const std::unordered_map<std::shared_ptr<Instrument>, int>& Portfolio::get_instruments() const {
        return instruments;
}

double Portfolio::compute_future_profit(const MarketScenario& scenario) {
    double total_profit = 0;
    const auto& scenario_data = scenario.get_scenario();
    auto instruments_copy = instruments; // Create a copy of the instruments map
    for (const auto& pair : instruments_copy) {
        auto it = scenario_data.find(pair.first);
        if (it != scenario_data.end()) {
            total_profit += pair.second * it->second; // Adjust the profit calculation based on the sign
        }
    }
    return total_profit;
}