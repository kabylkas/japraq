/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef QUESTION_H_
#define QUESTION_H_

// C++ libraries.
#include <string>

namespace japraq
{
    // Forward declarations.
    struct TableRow;

    class DecisionTreeQuestion {
    public:
        DecisionTreeQuestion() = default;
        void SetRightOperand(float right_operand);
        float GetRightOperand() const;
        virtual bool Evaluate(const TableRow& table_row) const = 0;

    private:
        std::string column_name_;
        float column_value_ = 0.0;
    };

    class QuestionEqualsTo : public DecisionTreeQuestion
    {
    public:
        bool Evaluate(const TableRow& table_row) const override;
    };

    class QuestionGreaterThanOrEqualsTo : public DecisionTreeQuestion
    {
    public:
        bool Evaluate(const TableRow& table_row) const override;
    };
} // namespace japraq

#endif // QUESTION_H_