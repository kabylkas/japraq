#pragma once
#include <vector>
#include <set>

enum class feature_t {
    NUMERIC,
    CATEGORICAL
};

struct row_t {
    std::vector<int> feature_vals;
    int label;
};

using row_ptrs_t = std::set<row_t*>;