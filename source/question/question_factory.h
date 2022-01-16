/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef QUESTION_FACTORY_H_
#define QUESTION_FACTORY_H_

// C++ libraries.
#include <memory>

// Local libraries.
#include "question.h"

namespace japraq
{
    // Forward declarations.
    enum class ColumnType;
    class QuestionFactory
    {
    public:
        std::shared_ptr<IQuestion> CreateQuestion(const ColumnType& type, const ColumnEntry& column_entry);
    };
} // namespace japraq
#endif // QUESTION_H_
