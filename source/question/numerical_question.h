/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef NUMERICAL_QUESTION_H_
#define NUMERICAL_QUESTION_H_

// Interface class.
#include "question.h"

namespace japraq
{
    // Forward declartions.
    struct ColumnEntry;
    class NumericalQuestion : public IQuestion
    {
    public:
        NumericalQuestion(const ColumnEntry& column_entry) : column_entry_(column_entry) {};
        bool Evaluate(const ColumnEntry& column_entriy) const override;

    private:
        const ColumnEntry& column_entry_;
    };
} // namespace japraq
#endif // CATEGORICAL_QUESTION_H_
