/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "numerical_table_column.h"

// C++ libraries.
#include <cassert>
#include <stdexcept>

namespace japraq
{
    float NumericalTableColumn::GetValue(uint32_t index)
    {
        float ret = 0.0;

        if (index < float_values_.size())
        {
            ret = float_values_[index];
        }

        return ret;
    }

    void NumericalTableColumn::AddEntry(const std::string& value)
    {
        try 
        {
            float_values_.push_back(std::stof(value));
        }
        catch (const std::exception& e)
        {
            assert(false);
        }
    }
} // namespace japraq
