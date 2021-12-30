#pragma once

#include <vector>
#include <set>
#include <string>
#include <memory>

struct feature_meta_t {
    feature_t type;
    std::string name;
    feature_meta_t() {}
    feature_meta_t(std::string str_type, std::string name) :
        type(get_type(str_type)), name(name) {}
    feature_meta_t(feature_t type, std::string name) :
        type(type), name(name) {}

    feature_t get_type(std::string str_type) {
        str_type = str_type.substr(0, 3);
        if (str_type == "cat") {
            return feature_t::CATEGORICAL;
        }
        if (str_type == "num") {
            return feature_t::NUMERIC;
        }
        if (str_type == "lab") {
            return feature_t::LABEL;
        }
    }
};
