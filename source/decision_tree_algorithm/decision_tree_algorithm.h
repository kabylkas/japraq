/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef DECISION_TREE_ALGORITHM_H_
#define DECISION_TREE_ALGORITHM_H_

// C++ libraries.
#include <vector>
#include <string>

namespace japraq
{
    // Forward declation.
    class DecisionTreeDataset;

    // Output of the Partion() method. 
    struct TwoParts
    {
        std::vector<uint32_t> true_row_indecies;
        std::vector<uint32_t> false_row_indecies;
    };

    class IDecisionTreeAlgorithm
    {
        // Providing rows to partition exposes internal represntation of the data. I should hide this.
        virtual bool Partition(const DecisionTreeDataset& dataset, const std::vector<uint32_t> rows_to_partition, TwoParts& two_parts, std::string& error_message) = 0;
    };
} // namespace japraq

#endif // DECISION_TREE_ALGORITHM_H_