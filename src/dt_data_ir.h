#pragma once

#include <string>
#include <map>
#include "defines.h"
#include "question.h"

// internal representation of data for decision tree
class dt_data_ir {
    public:
        dt_data_ir(std::string csv_file_path);
        dt_data_ir(const row_ptrs_t& rows);
        std::string get_cols();
        const row_ptrs_t& get_rows() const;
        const feature_meta_t& get_feature_meta_data(col_t col) const;

    private:
        std::map<col_t, feature_meta_t> feature_meta_data;
        std::map<col_t, std::map<uint32_t, std::string>> col_to_categ; 
        std::map<col_t, std::set<double>> unique_nums;

        row_ptrs_t rows;
        int find_encoding(uint32_t col, std::string value);

};