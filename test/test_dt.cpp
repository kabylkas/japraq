#include <vector>
#include <iostream>
#include "tree_node.h"
#include "question.h"
#include "defines.h"
#include "csv_ir.h"
#include "test_runner.h"

void basic_test() {
    row_t r1, r2, r3, r4, r5;
    r1 = {{1.0,1.1,1,1,1}, 1};
    r2 = {{2,2,2,2,2}, 0};
    r3 = {{1,2,1,4,1}, 1};
    r4 = {{2,2,1,4,1}, 2};
    r5 = {{1,2,1,1,1}, 0};

    const row_ptrs_t rows = {
        std::make_shared<row_t>(r1),
        std::make_shared<row_t>(r2),
        std::make_shared<row_t>(r3),
        std::make_shared<row_t>(r4),
        std::make_shared<row_t>(r5),
    };
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
    
    csv_ir ir("../../data/toy_2.csv");
    std::cout << ir.get_cols();

    tree_node tn3 = tree_node(ir.get_rows());
    std::cout << tn3.get_gini() << '\n';
}

int main() {
    test_runner tr;
    RUN_TEST(tr, basic_test);
}