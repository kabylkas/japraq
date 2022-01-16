/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "numerical_question.h"

// Local libraries.
#include "table_defines.h"

namespace japraq
{
    bool NumericalQuestion::Evaluate(const ColumnEntry& column_entry) const
    {
        return column_entry_.numerical_value >= column_entry.numerical_value;
    }
}
