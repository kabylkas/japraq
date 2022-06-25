/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef JAPRAQ_TREE_NODE_H_
#define JAPRAQ_TREE_NODE_H_

// C++ libraries.
#include <memory>
#include <vector>
#include <string>

namespace japraq
{
  // Forwared declations.
  class Question;
  struct DataPoint;

  class TreeNode
  {
  public:
    // Getters.
    bool GetDatasetIndicies(std::vector<uint32_t>& dataset_indicies, std::string& error_message) const;
    std::shared_ptr<TreeNode> GetFittingChild(const DataPoint& data_point) const;

    // Setters.
    void AddChild(const Question& question, const std::vector<uint32_t>& dataset_indicies);

    // Other.
    bool IsLeaf() const;

  private:
    struct Implementation;
    std::shared_ptr<Implementation> pimpl_;
  };
}

#endif // JAPRAQ_TREE_NODE_H_