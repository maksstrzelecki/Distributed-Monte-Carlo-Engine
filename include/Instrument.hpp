#pragma once

class Instrument {
public:
    virtual double get_value() = 0; // get value based on predictions
    virtual ~Instrument() = default;
};

