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
        /* 
         * BuildTree --
         *  Accepts the DecisionTreeDataset and build the decision based on the
         *  algorithm the inherting class implements.
         * 
         *  On successful build, the method return true and outputs a root_node.
         *  Otherwise, returns false and outputs error message.
         */
        virtual bool BuildTree
        (
            const DecisionTreeDataset& dataset,
            DecisionTreeNode& root_node,
            std::string& error_message
        ) = 0;

        virtual bool Infer(const DecisionTreeDataset& dataset, const DecisionTreeNode& root_node, const DataPoint& data_point, std::string& result, std::string& error_message);
        virtual ~IDecisionTreeAlgorithm() = 0;
    };
} // namespace japraq

#endif // DECISION_TREE_ALGORITHM_H_