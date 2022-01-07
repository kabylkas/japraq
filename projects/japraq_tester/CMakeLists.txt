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
)

# Set project source.
set (ALL_CPP
    # DecisionTreeDataset class.
    ${SOURCE_DIR}/decision_tree_dataset/decision_tree_dataset.cpp
)

# Adding target.
add_executable(main main.cpp ${ALL_HEADERS} ${ALL_CPP})

# Include directories.
target_include_directories(main PRIVATE
    ${SOURCE_DIR}/decision_tree_dataset
)