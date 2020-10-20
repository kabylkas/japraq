#pragma once
#include <set>
#include <utility> 
#include <map> 
#include "defines.h"
#include "question.h"

class tree_node {
    private:
        std::map<int, std::set<int>> unique_feature_vals;
        const row_ptrs_t& rows;
        const double gini;
        double gini_calc();

    public:
        tree_node(const row_ptrs_t& rows);
        std::pair<row_ptrs_t, row_ptrs_t> partition(const question& q);
        void print_rows();
        double get_gini();
};