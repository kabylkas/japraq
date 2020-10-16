#include "question.h"

bool question::eval(const row_t& row) const {
    if (this->type == feature_t::NUMERIC) {
        return row.feature_vals[this->feature] >= this->val;
    } else {
        return row.feature_vals[this->feature] == this->val;
    }
}