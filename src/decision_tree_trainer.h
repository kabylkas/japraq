/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0 (the "License").
 */
#ifndef DECISION_TREE_TRAINER_H_
#define DECISION_TREE_TRAINER_H_

// C++ libraries.
#include <string>

namespace japraq
{
    class DecisionTreeTrainer {
    public:
        /*
         * Train --
         * 
         * Accepts path to input csv file with training data.
         * 
         * On successful training returns true and generates model file in the specified location by output_model_file argument.
         * Otherwise return false and outputs corresponding message in error_message argument.
         */
        static bool Train(const std::string& input_csv_file, const std::string& output_model_file, std::string& error_message);

        // Explicitly remove constructors.
        DecisionTreeTrainer() = delete;
        DecisionTreeTrainer(const DecisionTreeTrainer&) = delete;
        DecisionTreeTrainer& operator=(const DecisionTreeTrainer&) = delete;
    };
} // namespace japraq

#endif // DECISION_TREE_TRAINER_H_