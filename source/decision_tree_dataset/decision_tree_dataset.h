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
        bool ReadCSV(const std::string& input_csv_files, std::string& error_message);
        bool GetLabel(uint32_t row_index, std::string& label, uint32_t& label_id, std::string& error_message) const;
        bool GetRow(uint32_t row_index, TableRow& table_row, std::string& error_message) const;
        bool GetColumn(const std::string& column_name, TableColumn& table_column, std::string& error_message) const;

        // Constructor restrictions.
        DecisionTreeDataset() = default;
        DecisionTreeDataset(const DecisionTreeDataset&) = delete;
        DecisionTreeDataset operator=(const DecisionTreeDataset&) = delete;

    private:
        struct DecisionTreeDatasetImplementation;
        std::unique_ptr<DecisionTreeDatasetImplementation> pimpl_;
    };
} // namespace japraq

#endif // DECISION_TREE_DATASET_H_