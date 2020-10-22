#pragma once
#include <cstdint>
#include "defines.h"

class question {
    private:
        const uint32_t feature;
        const double val;
        const feature_t type;

    public:
        question(uint32_t feature, double val, feature_t type) :
            feature(feature), val(val), type(type) {}

        bool eval(const row_t& row) const;
};