/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef QUESTION_H_
#define QUESTION_H_

namespace japraq
{
    // Forward declartions.
    struct ColumnEntry;
    struct IQuestion
    {
        virtual bool Evaluate(const ColumnEntry& column_entry) const = 0;
        virtual ~IQuestion() = default;
    };
} // namespace japraq
#endif // QUESTION_H_
