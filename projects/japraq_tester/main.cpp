/*
 * Copyright (c) 2021-2022 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
// Test library.
#include "synaq.h"

// C++ libraries.
#include <sstream>
#include <vector>

// Local libraries.
#include "decision_tree_dataset.h"
#include "table_defines.h"

// Constants.
static const char* kTestCsvDataPath = "C:/Users/kerei/japraq/projects/japraq_tester/test_data";

static void TestDecisionTreeDataset()
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

    // Check labels.
    std::string label;
    uint32_t label_id = 0;

    // Test GetLable() interface.
    // Expected labels.
    std::vector<std::string> expected_labels = { "programmer", "translator", "programmer" };
    uint32_t row_num = 0;
    for (const auto& expected_label : expected_labels)
    {
        bool is_label_read = dataset.GetLabel(row_num, label, label_id, error_message);
        REQUIRE(is_label_read);
        REQUIRE(label == expected_label);
        row_num++;
    }

    // Test GetRow() interface.
    japraq::TableRow row;
    bool is_row_read = dataset.GetRow(0, row, error_message);
    REQUIRE(is_row_read);
    REQUIRE(row.row_entries[0].column_entry.categorical_value == "nursultan");
    REQUIRE(row.row_entries[1].column_entry.numerical_value == 31.0);
    REQUIRE(row.row_entries[2].column_entry.categorical_value == "programmer");
    REQUIRE(row.row_entries[0].column_info.column_name == "name");
    REQUIRE(row.row_entries[0].column_info.column_type == japraq::ColumnType::kCategorical);
    REQUIRE(row.row_entries[1].column_info.column_name == "age");
    REQUIRE(row.row_entries[1].column_info.column_type == japraq::ColumnType::kNumercal);
    REQUIRE(row.row_entries[2].column_info.column_name == "occupation");
    REQUIRE(row.row_entries[2].column_info.column_type == japraq::ColumnType::kCategorical);

    is_row_read = dataset.GetRow(1, row, error_message);
    REQUIRE(is_row_read);
    REQUIRE(row.row_entries[0].column_entry.categorical_value == "arai");
    REQUIRE(row.row_entries[1].column_entry.numerical_value == 29.0);
    REQUIRE(row.row_entries[2].column_entry.categorical_value == "translator");
    REQUIRE(row.row_entries[0].column_info.column_name == "name");
    REQUIRE(row.row_entries[0].column_info.column_type == japraq::ColumnType::kCategorical);
    REQUIRE(row.row_entries[1].column_info.column_name == "age");
    REQUIRE(row.row_entries[1].column_info.column_type == japraq::ColumnType::kNumercal);
    REQUIRE(row.row_entries[2].column_info.column_name == "occupation");
    REQUIRE(row.row_entries[2].column_info.column_type == japraq::ColumnType::kCategorical);

    is_row_read = dataset.GetRow(2, row, error_message);
    REQUIRE(is_row_read);
    REQUIRE(row.row_entries[0].column_entry.categorical_value == "arman");
    REQUIRE(row.row_entries[1].column_entry.numerical_value == 38.0);
    REQUIRE(row.row_entries[2].column_entry.categorical_value == "programmer");
    REQUIRE(row.row_entries[0].column_info.column_name == "name");
    REQUIRE(row.row_entries[0].column_info.column_type == japraq::ColumnType::kCategorical);
    REQUIRE(row.row_entries[1].column_info.column_name == "age");
    REQUIRE(row.row_entries[1].column_info.column_type == japraq::ColumnType::kNumercal);
    REQUIRE(row.row_entries[2].column_info.column_name == "occupation");
    REQUIRE(row.row_entries[2].column_info.column_type == japraq::ColumnType::kCategorical);

    is_row_read = dataset.GetRow(3, row, error_message);
    REQUIRE(!is_row_read);

    is_row_read = dataset.GetRow(3213, row, error_message);
    REQUIRE(!is_row_read);

    is_row_read = dataset.GetRow(-1, row, error_message);
    REQUIRE(!is_row_read);

    // Test GetColumn() interface.
    japraq::TableColumn col;
    bool is_col_read = dataset.GetColumn(0, col, error_message);
    REQUIRE(is_col_read);
    REQUIRE(col.column_info.column_name == "name");
    REQUIRE(col.column_info.column_type == japraq::ColumnType::kCategorical);
    std::vector<std::string> expected_names = { "nursultan", "arai", "arman" };
    uint32_t entry_index = 0;
    for (const auto& col_entry : col.column_entries)
    {
        REQUIRE(col_entry.categorical_value == expected_names[entry_index]);
        entry_index++;
    }

    is_col_read = dataset.GetColumn(1, col, error_message);
    REQUIRE(is_col_read);
    REQUIRE(col.column_info.column_name == "age");
    REQUIRE(col.column_info.column_type == japraq::ColumnType::kNumercal);
    std::vector<float> expected_ages = { 31.0, 29.0, 38.0 };
    entry_index = 0;
    for (const auto& col_entry : col.column_entries)
    {
        REQUIRE(col_entry.numerical_value == expected_ages[entry_index]);
        entry_index++;
    }

    is_col_read = dataset.GetColumn(2, col, error_message);
    REQUIRE(is_col_read);
    REQUIRE(col.column_info.column_name == "occupation");
    REQUIRE(col.column_info.column_type == japraq::ColumnType::kCategorical);
    std::vector<std::string> expected_occupation = { "programmer", "translator", "programmer" };
    entry_index = 0;
    for (const auto& col_entry : col.column_entries)
    {
        REQUIRE(col_entry.categorical_value == expected_occupation[entry_index]);
        entry_index++;
    }

    is_col_read = dataset.GetColumn(3, col, error_message);
    REQUIRE(!is_col_read);

    is_col_read = dataset.GetColumn(3986, col, error_message);
    REQUIRE(!is_col_read);

    is_col_read = dataset.GetColumn(-3, col, error_message);
    REQUIRE(!is_col_read);

    // Read other test files.
    // Using the same dataset to read another file should return false.
    stream.str("");
    stream << kTestCsvDataPath << "/" << "test2.csv";
    is_read_successful = dataset.ReadCSV(stream.str(), error_message);
    REQUIRE(!is_read_successful);

    japraq::DecisionTreeDataset dataset_2;
    is_read_successful = dataset_2.ReadCSV(stream.str(), error_message);
    REQUIRE(is_read_successful);
}

int main()
{
    synaq::Synaq test_runner;
    RUN_TEST(test_runner, TestDecisionTreeDataset);
    return 0;
}