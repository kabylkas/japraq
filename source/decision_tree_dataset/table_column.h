/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef TABLE_COLUMN_H_
#define TABLE_COLUMN_H_

// C++ libraries.
#include <string>

namespace japraq
{
    class ITableColumn
    {
    public:
        virtual float GetValue(uint32_t index) = 0;
        virtual void AddEntry(const std::string& value) = 0;
        virtual ~ITableColumn() = 0;

    private:
        std::string column_name_;
    };

} // namespace japraq

#endif // TABLE_COLUMN_H_