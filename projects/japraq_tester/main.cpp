/*
 * Copyright (c) 2021-2022 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */

// Test library.
#include "synaq.h"

// C++ libraries.
#include <sstream>

// Local libraries.
#include "decision_tree_dataset.h"

// Constants.
static const char* kTestCsvDataPath = "C:/Users/kerei/japraq/projects/japraq_tester/test_data";

void TestDecisionTreeDataset()
{
    // Initialize dataset.
    japraq::DecisionTreeDataset dataset;

    // Form path to test csv file.
    std::stringstream stream;
    stream << kTestCsvDataPath << "/" << "test1.csv";

    // Read in data.
    std::string error_message;
    bool is_read_successful = dataset.ReadCSV(stream.str(), error_message);
    REQUIRE(is_read_successful);

    std::string label;
    uint32_t label_id = 0;
    bool is_label_read = dataset.GetLabel(0, label, label_id, error_message);
    REQUIRE(is_label_read);
}

int main()
{
    synaq::Synaq test_runner;
    RUN_TEST(test_runner, TestDecisionTreeDataset);
    return 0;
}