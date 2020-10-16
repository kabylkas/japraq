#pragma once
#include <vector>
#include <set>

enum class feature_t {
    NUMERIC,
    CATEGORICAL
};

using row_t = std::vector<int>;
using row_ptrs_t = std::set<row_t*>;