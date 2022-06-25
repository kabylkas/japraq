/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef QUESTION_H_
#define QUESTION_H_

namespace japraq
{
  // Forward declarations.
  class Attribute;

  enum class QuestionOperation
  {
    kEquals,
    kNotEquals,
    kGreaterThan
  };

  class Question
  {
  public:
    // Constructor for categorical question.
    Question(const Attribute& should_be, QuestionOperation operation);

    // Should be attribute must be always provided.
    Question() = delete;

    bool Ask(const DataPoint& data_point, const Attribute& attribute) const;

  private:
    struct Implementation;
    std::shared_ptr<Implementation> pimpl_;
  };
} // namespace japraq
#endif // QUESTION_H_
