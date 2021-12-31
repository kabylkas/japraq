/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "question.h"

namespace japraq
{
    void Question::SetRightOperand(float right_operand)
    {
        right_operand_ = right_operand;
    }

    float Question::GetRightOperand() const
    {
        return right_operand_;
    }

    bool QuestionEqualsTo::Evaluate(float left_operand)
    {
        return left_operand == GetRightOperand();
    }

    bool QuestionGreaterThanOrEqualsTo::Evaluate(float left_operand)
    {
        return left_operand >= GetRightOperand();
    }
} // namespace japraq