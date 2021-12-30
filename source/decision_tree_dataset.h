/*
 * Copyright (c) 2021 Kabylkas Labs.
 * Licensed under the Apache License, Version 2.0.
 */
#ifndef DECISION_TREE_DATASET_H_
#define DECISION_TREE_DATASET_H_

// C++ libraries.
#include <vector>

namespace japraq
{ 
    enum class FeatureType {
        kNumeric,
        kCategorical,
        kLabel,
        kUndefined
    };

    struct DatasetRow {
        std::vector<double> feature_vals;
        int label;
        uint32_t row_num;
    };

    using row_ptrs_t = std::set<std::shared_ptr<row_t>>;
    using col_t = uint32_t;
    // Internal representation of data for decision tree.
    struct DecisionTreeDataset
    {

    };
} // namespace japraq


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

#endif // DECISION_TREE_DATASET_H_