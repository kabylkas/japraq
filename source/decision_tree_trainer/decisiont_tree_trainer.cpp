/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "decision_tree_trainer.h"

// C++ libraries.
#include <fstream>
#include <sstream>

namespace japraq
{
    // STATIC FUNCTIONS - BEGIN.
    // STATIC FUNCTIONS - END.

    bool DecisionTreeTrainer::Train(const std::shared_ptr<IDecisionTreeAlgorithm>& algorithm, const std::string& input_csv_file, const std::string& output_model_file, std::string& error_message)
    {
        // 1. Read data.

        // 2. Run algorithm.partition(dataset, root_node, error_message);

        // 3. Dump data and root_node
    }
} // namespace japraq