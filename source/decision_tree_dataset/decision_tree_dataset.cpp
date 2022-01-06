/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#include "decision_tree_dataset.h"

// C++ libraries.
#include <fstream>
#include <cassert>
#include <map>
#include <sstream>

// Local libraries.
#include "table_defines.h"

namespace japraq
{
    // CONSTANTS.
    static const char* kStringErrorFailedToOpenCsv = "Error: Failed to open a CSV file.";
    static const char* kStringErrorUnrecognizedColumnType = "Error: Failed to read CSV. File contains unrecognized column type.";
    static const char* kStringErrorDataColumnsDonotMatch = "Error: Failed to read CSV. Number of data columns do not match number of header columns.";

    // CONSTANT MAPPINGS.
    static const std::map<std::string, ColumnType> kMapColumnTypeStringToEnum = {
        { "cat", ColumnType::kCategorical },
        { "num", ColumnType::kNumircal },
        { "lab", ColumnType::kCategorical }
    };

    // PIMPL DEFINTION.
    struct DecisionTreeDataset::DecisionTreeDatasetImplementation
    {
        // Table that stores the data.
        Table table;

        // Was table initizlized?
        bool is_init = false;

        // Mappings from string categorical names to uint32_t.
        // This was done for optimization purposes.
        std::map<std::string, uint32_t> map_string_to_uint;
    };

    bool DecisionTreeDataset::ReadCSV(const std::string& input_csv_file, std::string& error_message)
    {
        bool should_abort = false;

        // Allocate pimpl.
        pimpl_ = std::make_unique<DecisionTreeDatasetImplementation>();

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
            while(!should_abort && std::getline(column_stream, value, ';'))
            {
                // Allocate column.
                pimpl_->table.columns.push_back(TableColumn());
                auto& column = pimpl_->table.columns.back();

                // Parse current column.
                std::stringstream col_info_stream(value);
                std::string col_name, col_type;
                std::getline(col_info_stream, col_name, ':');
                std::getline(col_info_stream, col_type, ':');

                // Save value.
                column.column_info.column_name = col_name;
                if (kMapColumnTypeStringToEnum.count(col_type) > 0)
                {
                    column.column_info.column_type = kMapColumnTypeStringToEnum.at(col_type);
                }
                else
                {
                    should_abort = true;
                    error_message = kStringErrorUnrecognizedColumnType;
                }
            }
        }

        // Read the rest of the rows.
        if (!should_abort)
        {
            uint32_t row_num = 0;
            while (!should_abort && input_csv.good())
            {
                // Get the next line and pack into string stream.
                std::getline(input_csv, line);
                std::stringstream column_stream(line);

                // Stream out each column value.
                uint32_t column_num = 0;
                for (column_num = 0; std::getline(column_stream, value, ';'); ++column_num)
                {
                    auto& current_column = pimpl_->table.columns[column_num];

                    // Allocate new column entry.
                    current_column.column_entries.push_back(ColumnEntry());
                    auto& current_entry = current_column.column_entries.back();

                    // Sanity check: number of columns should match to number columns read
                    // in first line.
                    if (column_num < pimpl_->table.columns.size())
                    {
                        switch (current_column.column_info.column_type)
                        {
                            case ColumnType::kCategorical:
                            {
                                // Handle internal opimization of mapping.
                                const auto& map_iterator = pimpl_->map_string_to_uint.find(value);
                                uint32_t uint_value = 0;
                                if (map_iterator == pimpl_->map_string_to_uint.end())
                                {
                                    // Allocate an entry in the map.
                                    pimpl_->map_string_to_uint[value];

                                    // Set the map to the current size.
                                    size_t size = pimpl_->map_string_to_uint.size();
                                    pimpl_->map_string_to_uint[value] = size;
                                    uint_value = size;
                                }
                                else
                                {
                                    uint_value = map_iterator->second;
                                }

                                // Record the data.
                                current_entry.categorical_value = value;
                                current_entry.categorical_uint_value = uint_value;
                            }
                            break;

                            case ColumnType::kNumircal:
                            {
                                try
                                {
                                    current_entry.numerical_value = std::stof(value);
                                }
                                catch (const std::exception& e)
                                {
                                    assert(false);
                                }
                            }
                            break;

                            default:
                                break;
                        }
                    }
                    else
                    {
                        should_abort = true;
                        error_message = kStringErrorDataColumnsDonotMatch;
                    }
                }
            }
        }
        pimpl_->is_init = !should_abort;
        return !should_abort;
    }
} // namespace japraq