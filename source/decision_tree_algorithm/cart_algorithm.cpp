/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "cart_algorithm.h"

// C++ libraries.
#include <deque>
#include <functional>
#include <map>
#include <memory>

// Local libraries.
#include "decision_tree_dataset.h"
#include "decision_tree_node.h"
#include "table_defines.h"

namespace japraq
{
    // CONSTANTS.
    static const char* kStringErrorUndefinedColumnCategory = "Error: Undefined column category detected.";

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

    static void Partition
    (
        const TableColumn& column,
        const ColumnEntry& pivot_entry,
        const std::vector<uint32_t>& row_indicies,
        const std::function<bool(uint32_t, float)>& question,
        std::vector<uint32_t>& true_indicies,
        std::vector<uint32_t>& false_indicies
    )
    {
		for (uint32_t index : row_indicies)
		{
			// Get the entry.
			auto& column_entry = column.column_entries[index];

			// Partition based on the question.
			if (question(column_entry.categorical_uint_value, column_entry.numerical_value))
			{
				true_indicies.push_back(index);
			}
			else
			{
				false_indicies.push_back(index);
			}
		}
    }

    static bool BestPartition
    (
        const DecisionTreeDataset& dataset,
        const std::vector<uint32_t> row_indicies,
        std::vector<uint32_t>& true_indicies,
        std::vector<uint32_t>& false_indicies,
        std::string& error_message
    )
    {
        bool should_abort = false;

        // Determine the condition to compare against based on the column type.
        std::function<bool(uint32_t, float)> question;
        if (column.column_info.column_type == ColumnType::kCategorical)
        {
            question = [&](uint32_t categorical_uint_value, float numerical_value) {
                return categorical_uint_value == pivot_entry.categorical_uint_value;
            };
        }
        else if (column.column_info.column_type == ColumnType::kNumercal)
        {
            question = [&](uint32_t categorical_uint_value, float numerical_value) {
                return numerical_value >= pivot_entry.numerical_value;
            };
        }
        else
        {
            should_abort = true;
            error_message = kStringErrorUndefinedColumnCategory;
        }

    }
    // STATIC FUNCTIONS - END.

    bool CartAlgorithm::BuildTree(const DecisionTreeDataset& dataset, DecisionTreeNode& root_node, std::string& error_message)
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

    bool CartAlgorithm::Infer(const DecisionTreeDataset& dataset, const DecisionTreeNode& root_node, const DataPoint& data_point, std::string& result, std::string& error_message)
    {
        error_message = "Error: Function not implemented.";
        return false;
    }
}