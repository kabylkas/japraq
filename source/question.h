/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef QUESTION_H_
#define QUESTION_H_

namespace japraq
{
    class Question {
    public:
        Question() = default;
        void SetRightOperand(float right_operand);
        float GetRightOperand() const;
        virtual bool Evaluate(float left_operatnd) = 0;

    private:
        float right_operand_ = 0.0;
    };

    class QuestionEqualsTo : public Question
    {
    public:
        bool Evaluate(float left_operand) override;
    };

    class QuestionGreaterThanOrEqualsTo : public Question
    {
    public:
        bool Evaluate(float left_opearand) override;
    };
} // namespace japraq

#endif // QUESTION_H_