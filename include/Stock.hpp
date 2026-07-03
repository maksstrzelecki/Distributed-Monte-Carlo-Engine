#pragma once

#include "Instrument.hpp"
#include <string>

class Stock : public Instrument {
private:
    std::string name;
    double price;
public:
    Stock(std::string n, double p) : name(n), price(p) {}
    double get_value() override;
    ~Stock() = default;
};