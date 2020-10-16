#pragma once
#include <set>
#include <utility> 
#include "defines.h"
#include "question.h"

class tree_node {
    private:
        row_ptrs_t row_ptrs;
        double gini_calc();
        std::pair<row_ptrs_t, row_ptrs_t> partition(question q);
};