#include <vector>
#include <iostream>
#include "tree_node.h"
#include "question.h"
#include "defines.h"
#include "dt_data_ir.h"
#include "test_runner.h"

void basic_test() {
    dt_data_ir ir("/home/kabylkas/decision_tree/data/toy.csv");
    tree_node tn = tree_node(ir, ir.get_rows());
    tn.print_rows();

    question q = question(1, 16, feature_t::NUMERIC);
    auto [rows_1, rows_2] = tn.best_partition();

    tree_node tn_1 = tree_node(ir, rows_1);
    tree_node tn_2 = tree_node(ir, rows_2);
    tn_1.print_rows();
    tn_2.print_rows();
}

int main() {
    test_runner tr;
    RUN_TEST(tr, basic_test);
//    RUN_TEST(tr, question_test);
//    RUN_TEST(tr, partition_test);
}