/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef CATEGORICAL_TABLE_COLUMN_H_
#define CATEGORICAL_TABLE_COLUMN_H_

// C++ libraries.
#include <map>
#include <string>
#include <vector>

// Local libraries.
#include "table_column.h"

namespace japraq
{
    class CategoricalTableColumn : public ITableColumn
    {
    public:
        CategoricalTableColumn() = default;
        float GetValue(uint32_t index) override;
        void AddEntry(const std::string& value) override;

    private:
        std::map<std::string, uint32_t> string_values_to_uint_;
        std::vector<uint32_t> uint_values_;
    };
} // namespace japraq

#endif // CATEGORICAL_TABLE_COLUMN_H_