#include <vector>
#include "tree_node.h"
#include "defines.h"

int main() {
    std::vector<int> v1 = {0,0,0,0,0};
    std::vector<int> v2 = {1,0,1,0,1};
    row_t r1;
    r1.feature_vals = v1;
    r1.label = 1;
    row_t r2;
    r2.feature_vals = v2;
    r2.label = 0;
    row_t r3;
    r3.feature_vals = {1,3,5,6,5};
    r3.label = 2;
    const row_ptrs_t rows = {&r1, &r2, &r3};
    tree_node tn = tree_node(rows);
    tn.print_rows();
}