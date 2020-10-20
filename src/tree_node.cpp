#include "tree_node.h"
#include <iostream>
#include <map>

tree_node::tree_node(const row_ptrs_t& rows) : 
    rows(rows), 
    gini(gini_calc()) {}

double tree_node::gini_calc() {
    std::vector<int> labels;
    for (auto row : rows) {
        labels.push_back(row->label);
    }
    
    std::map<int, int> label_count;
    for (auto label : labels) {
        label_count[label];
        label_count[label]++;
    }

    double gini = 0;
    for (auto [label, count] : label_count) {
        double prob_of_label = 1.0*count/labels.size();
        double current_gini = prob_of_label*(1-prob_of_label);
        gini += current_gini;
    }
    return gini;
}

void tree_node::print_rows() {
    for (auto row : rows) {
        for (auto elem : row->feature_vals) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
}

std::pair<row_ptrs_t, row_ptrs_t> tree_node::partition(const question& q) {
    row_ptrs_t true_p;
    row_ptrs_t false_p;
    for (auto row : this->rows) {
        if (q.eval(*row)) {
            true_p.insert(row);
        } else {
            false_p.insert(row);
        }
    }

    return std::make_pair(true_p, false_p);
}

double tree_node::get_gini() {
    return this->gini;
}