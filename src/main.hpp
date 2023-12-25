#pragma once
#include "avl-tree.hpp"
#include "stdlib.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

void clear_graphs();

std::vector<int> generate_keys(int count);

void dump_tree(AvlTree &tree, int index);

void print_balance_info(AvlTree &tree);
