/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "decision_tree_trainer.h"

// C++ libraries.
#include <fstream>
#include <sstream>

namespace japraq
{
    // CONSTANTS.
    static const char* kStringErrorFailedToOpenCsv = "Error: Failed to open a CSV file.";

    // STATIC FUNCTIONS - BEGIN.
    static bool ReadCSV(const std::string& input_csv_file, std::string& error_message)
    {
        bool should_abort = false;

        // Open the file.
        std::ifstream input_csv(input_csv_file);
        if (!input_csv.is_open())
        {
            should_abort = false;
            error_message = kStringErrorFailedToOpenCsv;
        }

        // Read the first line in CSV, i.e. read the column names.
        std::string line;
        std::string value;
        if (!should_abort)
        {
            // Get first line into the "line" variable.
            std::getline(input_csv, line);
            std::stringstream column_stream(line);

            // Seperate by ";" and store in "value" variable.
            while(std::getline(column_stream, value, ';'))
            {
                std::stringstream feat_ss(value);
                std::string col_name, col_category;
                std::getline(feat_ss, col_name, ':');
                std::getline(feat_ss, col_category, ':');

                this->feature_meta_data[i];
                this->feature_meta_data[i] = feature_meta_t(col_category, col_name);
            } 
            for (uint32_t i=0; ; ++i) {
            }
        }

        // read the data
        uint32_t row_num = 0;
        while (in_csv.good()) {
            std::getline(in_csv, line);
            std::stringstream col_ss(line);
            std::shared_ptr new_row = std::make_shared<row_t>();
            new_row->row_num = row_num;
            ++row_num;
            this->rows.insert(new_row);
            for (col_t col=0; std::getline(col_ss, value, ';'); ++col) {
                switch (this->feature_meta_data[col].type)
                {
                    case feature_t::LABEL: {
                        uint32_t encoding = this->find_encoding(col, value);
                        new_row->label = encoding;
                        break;
                    }
                    case feature_t::CATEGORICAL: {
                        uint32_t encoding = this->find_encoding(col, value);
                        new_row->feature_vals.push_back(encoding);
                        break;
                    }
                    case feature_t::NUMERIC: {
                        double d = std::stod(value);
                        this->unique_nums[col];
                        this->unique_nums[col].insert(d);
                        new_row->feature_vals.push_back(d);
                        break;
                    }
                    default:
                        throw std::runtime_error("Non-existant feature category");
                        break;
                }
            }
        }
    }
    // STATIC FUNCTIONS - END.

    bool DecisionTreeTrainer::Train(const std::shared_ptr<IDecisionTreeAlgorithm>& algorithm, const std::string& input_csv_file, const std::string& output_model_file, std::string& error_message)
    {
        // 1. Read data.

        // 2. Run algorithm.partition(dataset, root_node, error_message);

        // 3. Dump data and root_node
    }
} // namespace japraq