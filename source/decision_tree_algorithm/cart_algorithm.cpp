/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "cart_algorithm.h"

// C++ libraries.
#include <deque>
#include <memory>

// Local libraries.
#include "decision_tree_node.h"
#include "question.h"

namespace japraq
{
    // STATIC FUNCTIONS - BEGIN.
    static double CalculateGini()
    {

    }

    static bool Partition(const DecisionTreeDataset& dataset, const Question& question, std::vector<uint32_t>& true_indicies, std::vector<uint32_t> false_indicies, std::string& error_message)
    {

    }

    static bool BestPartition
    (
        const DecisionTreeDataset& dataset,
        const std::vector<uint32_t> node_indicies,
        std::vector<uint32_t>& true_indicies,
        std::vector<uint32_t> false_indicies,
        std::string& error_message
    )
    {

    }
    // STATIC FUNCTIONS - END.

    bool CartAlgorighm::BuildTree(const DecisionTreeDataset& dataset, DecisionTreeNode& root_node, std::string& error_message)
    {
        bool ret = false;
        std::deque<std::shared_ptr<DecisionTreeNode>> nodes_to_process;    
        nodes_to_process.push_back(std::make_shared<DecisionTreeNode>(root_node));

        while(!nodes_to_process.empty())
        {
            auto& current_node = nodes_to_process.front();

            // Get datapoints of the current node.
            std::vector<uint32_t> node_indicies;
            std::vector<uint32_t> true_indicies;
            std::vector<uint32_t> false_indicies;
            bool is_retrieved = current_node->GetDatasetIndicies(node_indicies, error_message);

            // Partition the datapoints.
            if (is_retrieved)
            {
                bool is_partitioned = BestPartition(dataset, node_indicies, true_indicies, false_indicies, error_message);
                if (is_partitioned)
                {
                    current_node->SetTrueChild(true_indicies, error_message);
                    current_node->SetFalseChild(false_indicies, error_message);
                }
            }
        }
    }

    bool CartAlgorighm::Infer(const DecisionTreeDataset& dataset, const DecisionTreeNode& root_node, const DataPoint& data_point, std::string& result, std::string& error_message)
    {
        error_message = "Error: Function not implemented.";
        return false;
    }
}