#include "tree_node.h"
#include <iostream>

void tree_node::print_rows() {
    for (auto row : rows) {
        for (auto elem : row->feature_vals) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
}