#pragma once

#include "Instrument.hpp"
#include <unordered_map>

class MarketScenario;

class Portfolio {
private:
    std::unordered_map<std::shared_ptr<Instrument>, int> instruments; // instrument and its count in the portfolio
public:
    Portfolio(const std::unordered_map<std::shared_ptr<Instrument>, int>& instruments_map) : 
        instruments(instruments_map) {}

    const std::unordered_map<std::shared_ptr<Instrument>, int>& get_instruments() const;

    double compute_future_profit(const MarketScenario& scenario);
    ~Portfolio() = default;
};