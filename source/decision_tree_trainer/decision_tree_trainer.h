/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef DECISION_TREE_TRAINER_H_
#define DECISION_TREE_TRAINER_H_

// C++ libraries.
#include <memory>
#include <string>

namespace japraq
{
    class IDecisionTreeAlgorithm;
    class DecisionTreeTrainer {
    public:
        /*
         * Train --
         * 
         * Accepts DecisionTreeAlgorithm object and path to input csv file with training data.
         * 
         * On successful training returns true and generates model file in the specified location by output_model_file argument.
         * Otherwise return false and outputs corresponding message in error_message argument.
         */
        static bool Train(const std::shared_ptr<IDecisionTreeAlgorithm>& algorithm, const std::string& input_csv_file, const std::string& output_model_file, std::string& error_message);

        // Explicitly remove constructors.
        DecisionTreeTrainer() = delete;
        DecisionTreeTrainer(const DecisionTreeTrainer&) = delete;
        DecisionTreeTrainer& operator=(const DecisionTreeTrainer&) = delete;
    };
} // namespace japraq

#endif // DECISION_TREE_TRAINER_H_