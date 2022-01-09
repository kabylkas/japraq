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
    static const char* kStringErrorDatasetNotInit = "Error: Dataset not initialized.";
    static const char* kStringErrorRowIdxOutOfRange = "Error: Provided row index is out of range.";
    static const char* kStringErrorDatasetHasManyLabels = "Error: Multiple labels detected. Ensure that the dataset has only one label column.";

    // CONSTANT MAPPINGS.
    static const std::map<std::string, ColumnType> kMapColumnTypeStringToEnum = {
        { "cat", ColumnType::kCategorical },
        { "num", ColumnType::kNumercal },
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

        // Number of rows in the table.
        uint32_t num_rows = 0;

        // Is label set.
        bool is_label_index_set = false;
    };

    // IMPLEMENTATION OF THE CLASS.
    bool DecisionTreeDataset::ReadCSV(const std::string& input_csv_file, std::string& error_message)
    {
        bool should_abort = false;

        // Allocate pimpl.
        pimpl_ = std::make_shared<DecisionTreeDatasetImplementation>();

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

                    // If label, save the index of the column.
                    if (col_type == "lab")
                    {
                        if (!pimpl_->is_label_index_set)
                        {
                            pimpl_->table.label_column_index = pimpl_->table.columns.size() - 1;
                        }
                        else
                        {
                            should_abort = true;
                            error_message = kStringErrorDatasetHasManyLabels;
                        }
                    }
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

                    // Sanity check: number of columns should match to number
                    // columns read in the first line.
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

                            case ColumnType::kNumercal:
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

                // Sanity check: number of columns should match to number
                // columns read in the first line.
                if (column_num != pimpl_->table.columns.size())
                {
                    should_abort = true;
                    error_message = kStringErrorDataColumnsDonotMatch;
                }
            }
        }

        pimpl_->is_init = !should_abort;
        pimpl_->num_rows = pimpl_->table.columns[0].column_entries.size();
        return !should_abort;
    }

    bool DecisionTreeDataset::GetLabel(uint32_t row_index, std::string& label, uint32_t& label_id, std::string& error_message) const
    {
        bool should_abort = false;

        // Error handling.
        if (!pimpl_->is_init)
        {
            should_abort = true;
            error_message = kStringErrorDatasetNotInit;
        }
        else if (row_index >= pimpl_->num_rows)
        {
            should_abort = true;
            error_message = kStringErrorRowIdxOutOfRange;
        }

        // Get label if base checks passed.
        if (!should_abort)
        {
            auto& column = pimpl_->table.columns[pimpl_->table.label_column_index];

            // Pass the values back.
            label = column.column_entries[row_index].categorical_value;
            label_id = column.column_entries[row_index].categorical_uint_value;
        }

        return !should_abort;
    }

    bool DecisionTreeDataset::GetRow(uint32_t row_index, TableRow& table_row, std::string& error_message) const
    {
        bool should_abort = false;

        // Error handling.
        if (!pimpl_->is_init)
        {
            should_abort = true;
            error_message = kStringErrorDatasetNotInit;
        }
        else if (row_index >= pimpl_->num_rows)
        {
            should_abort = true;
            error_message = kStringErrorRowIdxOutOfRange;
        }

        // Get the row if base checks passed.
        if (!should_abort)
        {
            // Clear the rows.
            table_row.row_entries.clear();

            // Traverse all the columns to get the relevant row.
            for (const auto& column : pimpl_->table.columns)
            {
                // Allocate the entry.
                table_row.row_entries.push_back(RowEntry());
                auto& row_entry = table_row.row_entries.back();

                // Save the entry from the column.
                row_entry.column_entry = column.column_entries[row_index];
                row_entry.column_info = column.column_info;
            }
        }

        return !should_abort;
    }
} // namespace japraq