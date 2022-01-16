/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "categorical_question.h"

// Local libraries.
#include "table_defines.h"

namespace japraq
{
    bool CategoricalQuestion::Evaluate(const ColumnEntry& column_entry) const
    {
        return column_entry_.categorical_uint_value == column_entry.categorical_uint_value;
    }
}
