#include "dt_data_ir.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

dt_data_ir::dt_data_ir(std::string csv_file_path) {
}

std::string dt_data_ir::get_cols() {
    std::stringstream ss;
    for (auto [num, feat] : this->feature_meta_data) {
        ss << num << " -> [" << feat.name << "]\n";
    }
    ss << '\n';

    for (auto [num, encodings] : this->col_to_categ) {
        ss << num << ":\n";
        for (auto [num2, categ_name] : encodings) {
            ss << "  " << num2 << " -> " << categ_name << '\n';
        }
    }

    return ss.str();
}

int dt_data_ir::find_encoding(uint32_t col, std::string value) {
    this->col_to_categ[col];
    auto& categs = this->col_to_categ[col];
    int found_encoding = -1;
    for (auto [encoding, category] : categs) {
        if (category == value) {
            found_encoding = encoding;
            break;
        }
    }

    if (found_encoding >= 0) {
        return found_encoding;
    } else {
        uint32_t size = categs.size();
        categs[size];
        categs[size] = value;
        return size;
    }
}

const row_ptrs_t& dt_data_ir::get_rows() const {
    return this->rows;
}

const feature_meta_t& dt_data_ir::get_feature_meta_data(col_t col) const {
    return this->feature_meta_data.at(col);
}