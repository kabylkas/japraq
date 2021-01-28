#include "question.h"

bool question::eval(const row_t& row) const {
    if (this->type == feature_t::NUMERIC) {
        return row.feature_vals[this->feature] >= this->val;
    } else {
        return row.feature_vals[this->feature] == this->val;
    }
}

void question::print() const {
    std::cout << "Feature: " << this->feature;
    std::cout << "; Value: " << this->val;
    std::cout << "\n";
}
