/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef TABLE_H_
#define TABLE_H_

// C++ libraries.
#include <memory>
#include <vector>
#include <string>

namespace japraq
{
    enum class ColumnType
    {
        kCategorical,
        kNumircal,
        kUndefined
    };

    struct ColumnValue
    {
        ColumnType column_type = ColumnType::kUndefined;
        float numerical_value = 0.0;
        std::string categorical_value;
    };

    struct TableColumn
    {
        ColumnValue GetValue(uint32_t index);
        void AddEntry(const std::string& value);
        std::string column_name;
    };

    struct RowEntry
    {
        std::string column_name;
        double value;
    };

    struct TableRow
    {
        std::vector<RowEntry> row_entries;
    };

    class Table
    {
    public:
        bool ReadCSV(const std::string& input_csv_file);

    private:
        class TableImplementation;
        std::unique_ptr<TableImplementation> table_implementation_;
    };
} // namespace japraq

#endif // TABLE_H_