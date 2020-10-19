#include <vector>
#include <iostream>
#include "tree_node.h"
#include "question.h"
#include "defines.h"
#include "csv_ir.h"

int main() {
    row_t r1, r2, r3, r4, r5;
    r1 = {{1,1,1,1,1}, 1};
    r2 = {{2,2,2,2,2}, 0};
    r3 = {{1,2,1,4,1}, 1};
    r4 = {{2,2,1,4,1}, 2};
    r5 = {{1,2,1,1,1}, 0};

    const row_ptrs_t rows = {&r1, &r2, &r3, &r4, &r5};
    tree_node tn = tree_node(rows);
    tn.print_rows();
    std::cout << '\n';

    question q(0, 1, feature_t::CATEGORICAL);
    std::cout << q.eval(r1) << '\n';
    std::cout << q.eval(r2) << '\n';

    auto [rows1, rows2] = tn.partition(q);
    tree_node tn1 = tree_node(rows1);
    tree_node tn2 = tree_node(rows2);

    tn1.print_rows();
    std::cout << tn1.get_gini() << '\n';
    tn2.print_rows();
    std::cout << tn2.get_gini() << '\n';
    
    csv_ir ir("../data/toy.csv");
    std::cout << ir.get_cols();
}