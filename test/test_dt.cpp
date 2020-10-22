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

void question_test() {
    row_t r1, r2, r3, r4, r5;
    r1 = {{1,2,3,4,5}, 1};
    r2 = {{2,2,2,2,2}, 0};
    r3 = {{1,2,1,4,1}, 1};
    r4 = {{2,2,1,4,1}, 2};
    r5 = {{1,2,1,1,1}, 0};

    {
        question q = question(0, 1, feature_t::CATEGORICAL);
        MUST_BE_EQUAL(q.eval(r1), true);
        MUST_BE_EQUAL(q.eval(r2), false);
        MUST_BE_EQUAL(q.eval(r3), true);
        MUST_BE_EQUAL(q.eval(r4), false);
        MUST_BE_EQUAL(q.eval(r5), true);
    }

    {
        question q = question(1, 2, feature_t::CATEGORICAL);
        MUST_BE_EQUAL(q.eval(r1), true);
        MUST_BE_EQUAL(q.eval(r2), true);
        MUST_BE_EQUAL(q.eval(r3), true);
        MUST_BE_EQUAL(q.eval(r4), true);
        MUST_BE_EQUAL(q.eval(r5), true);
    }

    {
        question q = question(1, 1.5, feature_t::CATEGORICAL);
        MUST_BE_EQUAL(q.eval(r1), false);
        MUST_BE_EQUAL(q.eval(r2), false);
        MUST_BE_EQUAL(q.eval(r3), false);
        MUST_BE_EQUAL(q.eval(r4), false);
        MUST_BE_EQUAL(q.eval(r5), false);
    }

    {
        question q = question(1, 1.5, feature_t::NUMERIC);
        MUST_BE_EQUAL(q.eval(r1), true);
        MUST_BE_EQUAL(q.eval(r2), true);
        MUST_BE_EQUAL(q.eval(r3), true);
        MUST_BE_EQUAL(q.eval(r4), true);
        MUST_BE_EQUAL(q.eval(r5), true);
    }

    {
        question q = question(4, 1.5, feature_t::NUMERIC);
        MUST_BE_EQUAL(q.eval(r1), true);
        MUST_BE_EQUAL(q.eval(r2), true);
        MUST_BE_EQUAL(q.eval(r3), false);
        MUST_BE_EQUAL(q.eval(r4), false);
        MUST_BE_EQUAL(q.eval(r5), false);
    }
}

void partition_test() {
    row_t r1, r2, r3, r4, r5;
    r1 = {{1,2,3,4,5}, 1};
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

    {
        question q = question(4, 1.5, feature_t::NUMERIC);
        auto [rows1, rows2] = tn.partition(q);
        const row_ptrs_t expected_rows1 = {
            std::make_shared<row_t>(r1),
            std::make_shared<row_t>(r2)
        };
        std::cerr << rows1 << std::endl;
        std::cerr << expected_rows1 << std::endl;

        const row_ptrs_t expected_rows2 = {
            std::make_shared<row_t>(r3),
            std::make_shared<row_t>(r4),
            std::make_shared<row_t>(r5)
        };

        MUST_BE_EQUAL(rows1, expected_rows1);
        MUST_BE_EQUAL(rows2, expected_rows1);
    }
}

int main() {
    test_runner tr;
    RUN_TEST(tr, basic_test);
    RUN_TEST(tr, question_test);
    RUN_TEST(tr, partition_test);
}