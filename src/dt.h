#pragma once
#include "tree_node.h"
#include "dt_data_ir.h"

class dt {
  private:
    const dt_data_ir& ir;
    tree_node root_tn;

  public:
    dt() = default;
    explicit dt(const char* file_name);
    void train();
};