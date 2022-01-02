/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef DECISION_TREE_DATASET_H_
#define DECISION_TREE_DATASET_H_

// C++ libraries.
#include <map>
#include <memory>
#include <vector>
#include <string>

namespace japraq
{
    struct RowEntry
    {
        std::string column_name;
        double value;
    };

    struct TableRow
    {
        std::vector<RowEntry> row_entries;
    };

    // Internal representation of data for decision tree.
    class DecisionTreeDataset
    {
    public:
        uint32_t GetLabel(uint32_t row_index) const; 
        TableRow GetRow(uint32_t row_index) const;

    private:
        class DecisionTreeDatasetImplementation;
        std::unique_ptr<DecisionTreeDatasetImplementation> pimpl_;
    };
} // namespace japraq

#endif // DECISION_TREE_DATASET_H_