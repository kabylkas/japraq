/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */

#ifndef TABLE_H_
#define TABLE_H_

// C++ libraries.
#include <memory>
#include <string>

namespace japraq
{
    struct TableEntry
    {
        
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