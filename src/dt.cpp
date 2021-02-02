#include <queue>
#include <memory>
#include "dt.h"

dt::dt(const char* file_name) :
  ir(dt_data_ir(file_name)),
  root_tn(tree_node(ir, ir.get_rows())) {}

void dt::train() {
  std::queue<std::shared_ptr<tree_node>> q;
  q.push(std::make_shared<tree_node>(this->root_tn));
  while (q.size() > 0) {
  }
}