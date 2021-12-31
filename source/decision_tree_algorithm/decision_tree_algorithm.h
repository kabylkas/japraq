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
    class DecisionTreeNode;

    class IDecisionTreeAlgorithm
    {
        // Providing rows to partition exposes internal represntation of the data. I should hide this.
        virtual bool BuildTree(const DecisionTreeDataset& dataset, DecisionTreeNode& root_node, std::string& error_message) = 0;
    };
} // namespace japraq

#endif // DECISION_TREE_ALGORITHM_H_