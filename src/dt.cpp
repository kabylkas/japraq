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
    auto& curr = q.front();
    auto [rows1, rows2] = curr->best_partition();
    if (rows1.size() > 0 && rows2.size() > 0) {
      q.push(std::make_shared<tree_node>(tree_node(this->ir, rows1)));
      q.push(std::make_shared<tree_node>(tree_node(this->ir, rows2)));
    }
    q.pop();
  }
}