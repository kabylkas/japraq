#pragma once

#include <set>
#include <utility> 
#include <map> 
#include <memory>
#include "defines.h"
#include "question.h"
#include "dt_data_ir.h"

class tree_node {
    private:
        const dt_data_ir& data;
        const row_ptrs_t& rows;
        const double gini;
        double gini_calc(const row_ptrs_t& rows);
        std::shared_ptr<tree_node> left_node;
        std::shared_ptr<tree_node> right_node;

    public:
        tree_node(const dt_data_ir& data, const row_ptrs_t& rows);
        std::pair<row_ptrs_t, row_ptrs_t> partition(const question& q);
        std::pair<row_ptrs_t, row_ptrs_t> best_partition();
        void print_rows();
        double get_gini();
};