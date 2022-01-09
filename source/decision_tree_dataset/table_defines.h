/*
 * Copyright (c) 2021-2022 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef TABLE_DEFINES_H_
#define TABLE_DEFINES_H_

// C++ libraries.
#include <memory>
#include <vector>
#include <string>

namespace japraq
{
    enum class ColumnType
    {
        kCategorical,
        kNumercal,
        kUndefined
    };

    struct ColumnInfo
    {
        ColumnType column_type = ColumnType::kUndefined;
        std::string column_name;
    };

    struct ColumnEntry
    {
        float numerical_value = 0.0;
        std::string categorical_value;

        // For optimization purposes categorical
        // string values are converted to uint32_t.
        uint32_t categorical_uint_value;
    };

    struct TableColumn
    {
        ColumnInfo column_info;
        std::vector<ColumnEntry> column_entries;
    };

    struct RowEntry
    {
        ColumnInfo column_info;
        ColumnEntry column_entry;
    };

    struct TableRow
    {
        std::vector<RowEntry> row_entries;
    };

    struct Table
    {
        std::vector<TableColumn> columns;
        uint32_t label_column_index = 0;
    };
} // namespace japraq

#endif // TABLE_DEFINES_H_