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

    auto [rows_1, rows_2] = tn.best_partition();

    tree_node tn_1 = tree_node(ir, rows_1);
    tree_node tn_2 = tree_node(ir, rows_2);
    tn_1.print_rows();
    tn_2.print_rows();
}

void gini_test() {
    {
        dt_data_ir ir("/home/kabylkas/decision_tree/test/test_data/test1.csv");
        tree_node tn = tree_node(ir, ir.get_rows());
        double expected_gini = ((2.0/3.0)*(1.0/3.0) + (1.0/3.0)*(2.0/3.0));
        MUST_BE_EQUAL(ROUND_DOUBLE(tn.get_gini()), ROUND_DOUBLE(expected_gini));
    }

    {
        dt_data_ir ir("/home/kabylkas/decision_tree/test/test_data/test2.csv");
        tree_node tn = tree_node(ir, ir.get_rows());
        double expected_gini = (2.0/5.0)*(3.0/5.0); 
        expected_gini += (2.0/5.0)*(3.0/5.0);
        expected_gini += (1.0/5.0)*(4.0/5.0);
        MUST_BE_EQUAL(ROUND_DOUBLE(tn.get_gini()), ROUND_DOUBLE(expected_gini));
    }

    {
        dt_data_ir ir("/home/kabylkas/decision_tree/test/test_data/test3.csv");
        tree_node tn = tree_node(ir, ir.get_rows());
        double expected_gini = (4.0/9.0)*(5.0/9.0);
        expected_gini += (5.0/9.0)*(4.0/9.0);
        MUST_BE_EQUAL(ROUND_DOUBLE(tn.get_gini()), ROUND_DOUBLE(expected_gini));
    }

    {
        dt_data_ir ir("/home/kabylkas/decision_tree/test/test_data/test4.csv");
        tree_node tn = tree_node(ir, ir.get_rows());
        MUST_BE_EQUAL(ROUND_DOUBLE(tn.get_gini()), ROUND_DOUBLE(0));
    }

    {
        dt_data_ir ir("/home/kabylkas/decision_tree/test/test_data/test5.csv");
        tree_node tn = tree_node(ir, ir.get_rows());
        double expected_gini = (5.0/12.0)*(7.0/12.0);
        expected_gini += (6.0/12.0)*(6.0/12.0);
        expected_gini += (1.0/12.0)*(11.0/12.0);
        MUST_BE_EQUAL(ROUND_DOUBLE(tn.get_gini()), ROUND_DOUBLE(expected_gini));
    }
}

void best_partition_test() {
    {
        dt_data_ir ir("/home/kabylkas/decision_tree/test/test_data/test1.csv");
        tree_node tn = tree_node(ir, ir.get_rows());
        auto [rows1, rows2] = tn.best_partition();
        std::vector<uint32_t> expected_row1_nums = {0,2};
        std::vector<uint32_t> actual_row1_nums;
        for (auto row : rows1) {
            actual_row1_nums.push_back(row->row_num);
        }
        std::vector<uint32_t> expected_row2_nums = {1};
        std::vector<uint32_t> actual_row2_nums;
        for (auto row : rows2) {
            actual_row2_nums.push_back(row->row_num);
        }
        MUST_BE_EQUAL(actual_row1_nums, expected_row1_nums);
        MUST_BE_EQUAL(actual_row2_nums, expected_row2_nums);
    }

    {
        dt_data_ir ir("/home/kabylkas/decision_tree/test/test_data/test2.csv");
        tree_node tn = tree_node(ir, ir.get_rows());
        auto [rows1, rows2] = tn.best_partition();
        std::vector<uint32_t> expected_row1_nums = {2,3};
        std::vector<uint32_t> actual_row1_nums;
        for (auto row : rows1) {
            actual_row1_nums.push_back(row->row_num);
        }
        std::vector<uint32_t> expected_row2_nums = {0,1,4};
        std::vector<uint32_t> actual_row2_nums;
        for (auto row : rows2) {
            actual_row2_nums.push_back(row->row_num);
        }
        MUST_BE_EQUAL(actual_row1_nums, expected_row1_nums);
        MUST_BE_EQUAL(actual_row2_nums, expected_row2_nums);
    }

    {
        dt_data_ir ir("/home/kabylkas/decision_tree/test/test_data/test3.csv");
        tree_node tn = tree_node(ir, ir.get_rows());
        auto [rows1, rows2] = tn.best_partition();
        std::cout << rows1 << "\n";
        std::cout << rows2 << "\n";
        std::vector<uint32_t> expected_row1_nums = {2,3};
        std::vector<uint32_t> actual_row1_nums;
        for (auto row : rows1) {
            actual_row1_nums.push_back(row->row_num);
        }
        std::vector<uint32_t> expected_row2_nums = {0,1,4};
        std::vector<uint32_t> actual_row2_nums;
        for (auto row : rows2) {
            actual_row2_nums.push_back(row->row_num);
        }
        //MUST_BE_EQUAL(actual_row1_nums, expected_row1_nums);
        //MUST_BE_EQUAL(actual_row2_nums, expected_row2_nums);
    }
}

int main() {
    test_runner tr;
    RUN_TEST(tr, basic_test);
    RUN_TEST(tr, gini_test);
    RUN_TEST(tr, best_partition_test);
//    RUN_TEST(tr, partition_test);
}