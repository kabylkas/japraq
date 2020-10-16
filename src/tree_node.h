#pragma once
#include <set>
#include <utility> 
#include <map> 
#include "defines.h"
#include "question.h"

class tree_node {
    private:
        std::map<int, std::set<int>> unique_feature_vals;
        const row_ptrs_t rows;
        double gini_calc();
        std::pair<row_ptrs_t, row_ptrs_t> partition(question q);

    public:
        tree_node(row_ptrs_t rows) : rows(rows) {};
        void print_rows();
};