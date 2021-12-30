/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "categorical_table_column.h"

namespace japraq
{
    float CategoricalTableColumn::GetValue(uint32_t index)
    {
        float ret = 0.0;

        if (index < uint_values_.size())
        {
            ret = static_cast<float>(uint_values_[index]);
        }

        return ret;
    }

    void CategoricalTableColumn::AddEntry(const std::string& value)
    {
        const auto& map_iterator = string_values_to_uint_.find(value);

        uint32_t uint_value = 0;
        if (map_iterator == string_values_to_uint_.end())
        {
            string_values_to_uint_[value];
            string_values_to_uint_[value] = string_values_to_uint_.size();
            uint_value = string_values_to_uint_.size();
        }
        else
        {
            uint_value = map_iterator->second;
        }

        uint_values_.push_back(uint_value);
    }
} // namespace japraq
