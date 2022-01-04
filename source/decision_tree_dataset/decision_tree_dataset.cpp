/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "decision_tree_dataset.h"

// C++ libraries.

// Local libraries.
#include "table_defines.h"

namespace japraq
{
    class DecisionTreeDataset::DecisionTreeDatasetImplementation
    {
        public:
            DecisionTreeDatasetImplemenation() = default;

        private:
            Table table_;
    }
} // namespace japraq