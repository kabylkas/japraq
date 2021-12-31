/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef CART_ALGORITHM_H_
#define CART_ALGORITHM_H_

// C++ libraries.
#include <string>

// Interface.
#include "decision_tree_algorithm.h"

namespace japraq
{
    class CartAlgorighm : public IDecisionTreeAlgorithm
    {
    public:
        bool BuildTree(const DecisionTreeDataset& dataset, DecisionTreeNode& root_node, std::string& error_message) override;
    };
} // namespace japraq

#endif // CART_ALGORITHM_H_