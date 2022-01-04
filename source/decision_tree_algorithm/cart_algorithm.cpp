/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "cart_algorithm.h"

// C++ libraries.
#include <deque>
#include <map>
#include <memory>

// Local libraries.
#include "decision_tree_dataset.h"
#include "decision_tree_node.h"
#include "question.h"

namespace japraq
{
    // STATIC FUNCTIONS - BEGIN.
    static double CalculateGiniImpurity(const DecisionTreeDataset& dataset, std::vector<uint32_t> row_indicies)
    {
        // Create the histogram of labels for the given indicies.
        std::map<uint32_t, uint32_t> histogram;
        for (uint32_t index : row_indicies)
        {
            // Get label.
            uint32_t label = dataset.GetLabel(index);

            // Update histogram.
            histogram[label];
            ++histogram[label];
        }

        // Calculate gini.
        uint32_t num_indicies = row_indicies.size();
        double gini = 0.0;
        for (const auto& histogram_data : histogram)
        {
            double probability = static_cast<double>(histogram_data.second) / num_indicies;
            gini += probability * probability;
        }

        return (1.0 - gini);
    }

    static bool Partition
    (
        const DecisionTreeDataset& dataset,
        const std::vector<uint32_t>& row_indicies,
        const Question& question,
        std::vector<uint32_t>& true_indicies,
        std::vector<uint32_t> false_indicies,
        std::string& error_message
    )
    {
        for (uint32_t index : row_indicies)
        {
            const auto& row = dataset.GetRow(index);
        }
    }

    static bool BestPartition
    (
        const DecisionTreeDataset& dataset,
        const std::vector<uint32_t> row_indicies,
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