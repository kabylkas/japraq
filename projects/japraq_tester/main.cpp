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
static const char* kTestCsvDataPath = "/home/kabylkas/japraq/projects/japraq_tester/test_data";

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
}

int main()
{
    synaq::Synaq test_runner;
    return 0;
}