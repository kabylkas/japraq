#include "dt.h"

int main() {
  dt decision_tree = dt("../data/toy.csv");
  decision_tree.train();
  return 0;
}