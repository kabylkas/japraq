/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "question_factory.h"

// Local libraries.
#include "table_defines.h"
#include "categorical_question.h"
#include "numerical_question.h"

namespace japraq
{
	std::shared_ptr<IQuestion> QuestionFactory::CreateQuestion(const ColumnType& type, const ColumnEntry& column_entry)
	{
		std::shared_ptr<IQuestion> ret;

		switch (type)
		{
		case ColumnType::kCategorical:
			ret = std::make_shared<CategoricalQuestion>(column_entry);
			break;
		case ColumnType::kNumercal:
			ret = std::make_shared<NumericalQuestion>(column_entry);
			break;
		default:
			break;
		}

		return ret;
	}
}
