#include "tree_node.h"
#include <iostream>
#include <map>

tree_node::tree_node(const dt_data_ir& data, const row_ptrs_t& rows) : 
    data(data),
    rows(rows), 
    gini(gini_calc(rows)) {}

double tree_node::gini_calc(const row_ptrs_t& rows) {
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
        std::cout << row->label;
        std::cout << '\n';
    }
    std::cout << '\n';
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

std::pair<row_ptrs_t, row_ptrs_t> tree_node::best_partition() {
    double best_gini = 2;
    row_ptrs_t best_1, best_2;
    for (auto row : this->rows) {
        for (col_t col = 0; col < row->feature_vals.size(); ++col) {
            // generate a question
            question q = question(col, row->feature_vals[col], data.get_feature_meta_data(col).type);

            // partition based on the question
            auto [row1, row2] = this->partition(q);

            // calculate the information gain
            double gini1 = this->gini_calc(row1);
            double gini2 = this->gini_calc(row2);
            size_t row_num = this->rows.size();
            double ave = (row1.size()/row_num*gini1) + (row2.size()/row_num*gini2);
            if (this->gini - ave < best_gini) {
                best_1 = row1;
                best_2 = row2;
                best_gini = this->gini - ave;
            }
        }
    }

    return std::make_pair(best_1, best_2);
}

double tree_node::get_gini() {
    return this->gini;
}