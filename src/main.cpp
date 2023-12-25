#include "main.hpp"

static const char *cc_red = "\E[31m";
static const char *cc_reset = "\E[37m";

static const fs::path graphs_dir = "graphs";

int main() {
  srand(time(0));

  clear_graphs();

  AvlTree tree;

  std::vector<int> keys = generate_keys(10);

  int step_i = 0;

  for (auto k : keys) {
    tree.SetValue(k, {k});
    std::cout << k << " key added" << std::endl;

    bool is_valid = tree.IsValidTree();
    if (!is_valid) {
      std::cout << cc_red;
      std::cout << "not valid" << std::endl;
      std::cout << cc_reset;
    }

    dump_tree(tree, step_i++);
    print_balance_info(tree);
  }

  for (auto k : keys) {
    std::cout << tree.FindValue(k).val << std::endl;
  }
}

void clear_graphs() {
  for (const auto &entry : fs::directory_iterator(graphs_dir)) {
    if (!fs::is_regular_file(entry.path())) {
      continue;
    }

    fs::remove(entry.path());
  }
}

std::vector<int> generate_keys(int count) {
  std::vector<int> keys;

  int d = 1;
  for (int i = 0; i < count; i++) {
    keys.push_back(rand() % 1000);
    d = -d;
  }

  return keys;
}

void dump_tree(AvlTree &tree, int index) {
  std::string filename = std::string("graph") + std::to_string(index) + ".dot";

  std::ofstream file(graphs_dir / filename, std::ios::binary);

  tree.Dump(file);

  file.close();
}

void print_balance_info(AvlTree &tree) {
  int min, max;
  bool is_balanced = tree.IsBalanced(min, max);

  if (is_balanced) {
    return;
  }

  std::cout << cc_red;
  std::cout << "not balanced" << std::endl;
  std::cout << "min: " << min << " max: " << max << std::endl;
  std::cout << cc_reset;
}
