#pragma once
#include <string>
#include <map>
#include "defines.h"

class csv_ir {
    public:
        csv_ir(std::string csv_file_path);
        std::string get_cols();
    private:
        std::map<uint32_t, feature_meta_t> feature_meta_data;
        std::map<uint32_t, std::map<uint32_t, std::string>> int_to_categ; 
        row_ptrs_t rows;

};