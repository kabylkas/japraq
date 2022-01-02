/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef DECISION_TREE_NODE_H_
#define DECISION_TREE_NODE_H_

// C++ libraries.
#include <memory>
#include <vector>

namespace japraq
{
    // Forwared declations.
    class Question;

    class DecisionTreeNode
    {
    public:
        // Getters.
        bool GetQuestion(Question& question, std::string& error_message) const;
        bool GetDatasetIndicies(std::vector<uint32_t>& dataset_indicies_, std::string& error_message) const;

        // Setters.
        bool SetQuestion(const Question& question, std::string& error_message);
        bool SetDatasetIndicies(const std::vector<uint32_t>& dataset_indicies_, std::string& error_message);
        bool SetTrueChild(const std::vector<uint32_t>& child_dataset_indicies, std::string& error_message);
        bool SetFalseChild(const std::vector<uint32_t>& child_dataset_indicies, std::string& error_message);

        // Other.
        bool IsLeaf() const;

    private:
        struct DecisionTreeNodeImplementation;
        std::unique_ptr<DecisionTreeNodeImplementation> pimpl_;
    };
}

#endif // DECISION_TREE_NODE_H_