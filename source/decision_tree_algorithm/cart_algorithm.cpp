/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "cart_algorithm.h"

// C++ libraries.
#include <deque>
#include <memory>

namespace japraq
{
    bool CartAlgorighm::BuildTree(const DecisionTreeDataset& dataset, DecisionTreeNode& root_node, std::string& error_message)
    {
        bool ret = false;
        std::deque<std::shared_ptr<DecisionTreeNode>> nodes_to_process;    
        nodes_to_process.push_back(std::make_shared<DecisionTreeNode>(root_node));

        while(!nodes_to_process.empty())
        {
            auto& current_node = nodes_to_process.front();
        }
    }

    bool CartAlgorighm::Infer(const DecisionTreeDataset& dataset, const DecisionTreeNode& root_node, const DataPoint& data_point, std::string& result, std::string& error_message)
    {
        error_message = "Function not implemented.";
        return false;
    }
}