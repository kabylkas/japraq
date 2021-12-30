/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef NUMERICAL_TABLE_COLUMN_H_
#define NUMERICAL_TABLE_COLUMN_H_

// C++ libraries.
#include <map>
#include <string>
#include <vector>

// Local libraries.
#include "table_column.h"

namespace japraq
{
    class NumericalTableColumn : public ITableColumn
    {
    public:
        NumericalTableColumn() = default;
        float GetValue(uint32_t index) override;
        void AddEntry(const std::string& value) override;

    private:
        std::vector<float> float_values_;
    };

} // namespace japraq

#endif // NUMERICAL_TABLE_COLUMN_H_