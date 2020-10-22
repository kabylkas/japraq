#pragma once
#include <string>
#include <map>
#include "defines.h"

class csv_ir {
    public:
        csv_ir(std::string csv_file_path);
        std::string get_cols();
        const row_ptrs_t& get_rows() const;

    private:
        std::map<uint32_t, feature_meta_t> feature_meta_data;
        std::map<uint32_t, std::map<uint32_t, std::string>> int_to_categ; 
        std::map<uint32_t, std::set<double>> unique_nums;
        row_ptrs_t rows;
        int find_encoding(uint32_t col, std::string value);

};