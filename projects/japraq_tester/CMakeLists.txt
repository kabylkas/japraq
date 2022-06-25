# Copyright (c) 2021-2022 Kabylkas Labs.
# Licensed under the Apache License, Version 2.0.
cmake_minimum_required(VERSION 3.0)

# Set project directories.
set (PROJECTS_DIR ../../projects)
set (SOURCE_DIR ../../source)

# Set project headers.
set (ALL_HEADERS
  # Test library.
  ${PROJECTS_DIR}/japraq_tester/synaq.h

  # DecisionTreeDataset class.
  ${SOURCE_DIR}/decision_tree_dataset/decision_tree_dataset.h
  ${SOURCE_DIR}/decision_tree_dataset/table_defines.h

  # DecisionTreeAlgorithm classes.
  ${SOURCE_DIR}/decision_tree_algorithm/decision_tree_algorithm.h
  ${SOURCE_DIR}/decision_tree_algorithm/cart_algorithm.h

  # Question class.
  ${SOURCE_DIR}/question/question.h
  ${SOURCE_DIR}/question/question_factory.h
  ${SOURCE_DIR}/question/categorical_question.h
  ${SOURCE_DIR}/question/numerical_question.h

  # DecisionTreeNode class.
  ${SOURCE_DIR}/common/tree_node.h
)

# Set project source.
set (ALL_CPP
  # DecisionTreeDataset class.
  ${SOURCE_DIR}/decision_tree_dataset/decision_tree_dataset.cpp

  # DecisionTreeAlgorithm classes.
  ${SOURCE_DIR}/decision_tree_algorithm/cart_algorithm.cpp

  # Question class.
  ${SOURCE_DIR}/question/question_factory.cpp
  ${SOURCE_DIR}/question/categorical_question.cpp
  ${SOURCE_DIR}/question/numerical_question.cpp

  # DecisionTreeNode class.
  ${SOURCE_DIR}/common/tree_node.cpp
)

# Adding target.
add_executable(japraq_tester main.cpp ${ALL_HEADERS} ${ALL_CPP})

# Include directories.
target_include_directories(japraq_tester PRIVATE
  ${SOURCE_DIR}/common
  ${SOURCE_DIR}/decision_tree_dataset
  ${SOURCE_DIR}/decision_tree_algorithm
  ${SOURCE_DIR}/question
)