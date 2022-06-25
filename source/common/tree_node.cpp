/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "tree_node.h"

// Local libraries.
#include "question.h"

namespace japraq
{
  struct TreeNodeChild
  {
    Question question;
    std::shared_ptr<TreeNode> child_pointer
  };

  struct TreeNode::Implementation
  {
      std::vector<TreeNodeChild> children;
  };

  TreeNode::DecisionTreeNode()
      : pimpl_(std::make_shared<Implementation>(new Implementation())) {}

  bool DecisionTreeNode::GetDatasetIndicies(std::vector<uint32_t>& dataset_indicies_, std::string& error_message) const
  {
  }

  bool DecisionTreeNode::IsLeaf() const
  {
      return (pimpl_->true_child == nullptr && pimpl_->false_child == nullptr);
  }
}
