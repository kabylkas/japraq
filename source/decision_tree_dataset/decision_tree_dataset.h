/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef DECISION_TREE_DATASET_H_
#define DECISION_TREE_DATASET_H_

// C++ libraries.
#include <memory>
#include <string>

namespace japraq
{
    // Forward declarations.
    struct TableRow;
    struct TableColumn;

    // Internal representation of data for decision tree.
    class DecisionTreeDataset
    {
    public:
        bool ReadCSV(const std::string& input_csv_file, std::string& error_message);
        bool ReadModel(const std::string& input_model_file, std::string& error_message);
        bool GetLabel(const uint32_t row_index, std::string& label, uint32_t& label_id, std::string& error_message) const;
        bool GetRow(const uint32_t row_index, TableRow& table_row, std::string& error_message) const;
        bool GetColumn(const uint32_t column_index, TableColumn& table_column, std::string& error_message) const;

        // Constructor restrictions.
        DecisionTreeDataset() = default;
        DecisionTreeDataset(const DecisionTreeDataset&) = delete;
        DecisionTreeDataset operator=(const DecisionTreeDataset&) = delete;

    private:
        struct DecisionTreeDatasetImplementation;
        std::shared_ptr<DecisionTreeDatasetImplementation> pimpl_;
    };
} // namespace japraq
#endif // DECISION_TREE_DATASET_H_