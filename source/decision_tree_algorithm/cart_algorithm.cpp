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
#include "question_factory.h"

namespace japraq
{
    // TYPE DEFINITIONS.
    using QuestionPointerList = std::vector<std::shared_ptr<IQuestion>>;

    // CONSTANTS.
    static const char* kStringErrorUndefinedColumnCategory = "Error: Undefined column category detected.";

    // STATIC FUNCTIONS.
    static double CalculateGiniImpurity(const DecisionTreeDataset& dataset, const std::vector<uint32_t>& row_indicies, std::string& error_message)
    {
        // Create the histogram of labels for the given indicies.
        std::map<uint32_t, uint32_t> histogram;
        for (const uint32_t index : row_indicies)
        {
            // Get label.
            uint32_t label_id = 0;
            std::string label;
            bool is_label_retrieved = dataset.GetLabel(index, label, label_id, error_message);

            // Update histogram.
            histogram[label_id];
            ++histogram[label_id];
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
        const std::shared_ptr<IQuestion> question,
        const std::vector<uint32_t>& row_indicies,
        std::vector<uint32_t>& true_indicies,
        std::vector<uint32_t>& false_indicies
    )
    {
		for (uint32_t index : row_indicies)
		{
			// Get the entry.
			auto& column_entry = column.column_entries[index];

			// Partition based on the question.
			if (question->Evaluate(column_entry))
			{
				true_indicies.push_back(index);
			}
			else
			{
				false_indicies.push_back(index);
			}
		}
    }

    static void GenerateQuestionsFromColumn
    (
        const TableColumn& column,
        QuestionPointerList& all_questions
    )
    {

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

        for (uint32_t column_index = 0;
            !should_abort && column_index < dataset.GetColumnCount();
            ++column_index)
        {
            TableColumn column;
            bool is_column_retrieved = dataset.GetColumn(column_index, column, error_message);

            if (is_column_retrieved)
            {
                // Generate all questions.
                QuestionPointerList all_questions;
                GenerateQuestionsFromColumn(column, all_questions);

                // Do all partitions.
                std::vector<uint32_t> temp_true_indicies;
                std::vector<uint32_t> temp_false_indicies;
                for (auto question_iterator = all_questions.begin();
                    !should_abort && question_iterator != all_questions.end();
                    ++question_iterator)
                {
                    // Dereference the question.
                    const auto& question = *question_iterator;

                    // Clear the partitioned vectors.
                    temp_true_indicies.clear();
                    temp_false_indicies.clear();

                    // Partition.
                    Partition(column, question, row_indicies, temp_true_indicies, temp_false_indicies);

                    // Calculate gini.
                }
            }
            else
            {
                should_abort = true;
            }
        }

        return !should_abort;
    }

    // CLASS IMPLEMENTATION.
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