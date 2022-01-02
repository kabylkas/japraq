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
    struct DataPoint;

    class IDecisionTreeAlgorithm
    {
        virtual bool BuildTree(const DecisionTreeDataset& dataset, DecisionTreeNode& root_node, std::string& error_message) = 0;
        virtual bool Infer(const DecisionTreeDataset& dataset, const DecisionTreeNode& root_node, const DataPoint& data_point, std::string& result, std::string& error_message);
        virtual ~IDecisionTreeAlgorithm() = 0;
    };
} // namespace japraq

#endif // DECISION_TREE_ALGORITHM_H_