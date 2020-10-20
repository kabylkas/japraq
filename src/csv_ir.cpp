#include "csv_ir.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

csv_ir::csv_ir(std::string csv_file_path) {
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
        row_t* new_row = new row_t();
        this->rows.insert(new_row);
        for (uint32_t i=0; std::getline(col_ss, value, ';'); ++i) {
            switch (this->feature_meta_data[i].type)
            {
                case feature_t::LABEL: {
                    uint32_t encoding = this->find_encoding(i, value);
                    new_row->label = encoding;
                    break;
                }
                case feature_t::CATEGORICAL: {
                    uint32_t encoding = this->find_encoding(i, value);
                    new_row->feature_vals.push_back(encoding);
                    break;
                }
                case feature_t::NUMERIC:
                    new_row->feature_vals.push_back(std::stoi(value));
                    break;
                default:
                    throw std::runtime_error("Non-existant feature category");
                    break;
            }
        }
    }
}

csv_ir::~csv_ir() {
    for (auto row : rows) {
        delete row;
    }
}

std::string csv_ir::get_cols() {
    std::stringstream ss;
    for (auto [num, feat] : this->feature_meta_data) {
        ss << num << " -> [" << feat.name << "]\n";
    }
    ss << '\n';

    for (auto [num, encodings] : this->int_to_categ) {
        ss << num << ":\n";
        for (auto [num2, categ_name] : encodings) {
            ss << "  " << num2 << " -> " << categ_name << '\n';
        }
    }

    return ss.str();
}

int csv_ir::find_encoding(uint32_t col, std::string value) {
    this->int_to_categ[col];
    auto& categs = int_to_categ[col];
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

const row_ptrs_t& csv_ir::get_rows() const {
    return this->rows;
}