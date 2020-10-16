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
    const row_ptrs_t rows = {&r1, &r2};
    tree_node tn = tree_node(rows);
    tn.print_rows();
}