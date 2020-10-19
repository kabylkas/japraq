#pragma once
#include <vector>
#include <set>
#include <string>

enum class feature_t {
    NUMERIC,
    CATEGORICAL,
    LABEL
};

struct feature_meta_t {
    feature_t type;
    std::string name;
};

struct row_t {
    std::vector<int> feature_vals;
    int label;
};

using row_ptrs_t = std::set<row_t*>;