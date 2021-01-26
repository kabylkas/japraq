#include "dt_data_ir.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

dt_data_ir::dt_data_ir(std::string csv_file_path) {
    std::ifstream in_csv(csv_file_path);
    if (!in_csv.is_open()) {
        throw std::runtime_error("Failed to open the file");
    }

    // read first line: col names
    std::string line, value;
    if (in_csv.good()) {
        std::getline(in_csv, line);
        std::stringstream col_ss(line);
        for (uint32_t i=0; std::getline(col_ss, value, ';'); ++i) {
            std::stringstream feat_ss(value);
            std::string col_name, col_category;
            std::getline(feat_ss, col_name, ':');
            std::getline(feat_ss, col_category, ':');

            this->feature_meta_data[i];
            this->feature_meta_data[i] = feature_meta_t(col_category, col_name);
        }
    }

    // read the data
    while (in_csv.good()) {
        std::getline(in_csv, line);
        std::stringstream col_ss(line);
        std::shared_ptr new_row = std::make_shared<row_t>();
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