#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

constexpr char* file_mini_test = "data/samples/0mini.in";
constexpr char* file_small_test = "data/samples/1small.in";
constexpr char* file_med_test = "data/samples/2med.in";
constexpr char* file_large_test = "data/samples/3large.in";
constexpr char* file_huge_test = "data/samples/4huge.in";
constexpr char* file_graph500_small_test =
    "data/graph500small/graph500small.in";

#include <graph.hpp>

void read_file_and_exec(std::string file_name)
{
  std::ifstream file(file_name, std::ios::in);
  if (file.is_open()) {
    std::string line;
    int n, m, a, b;
    std::vector<edge_t> edges;
    file >> n >> m;
    std::cout << "Reading file: " << file_name << std::endl;
    std::cout << "Vertices=" << n << " Edges=" << m << std::endl;
    while (file >> a >> b) {
      edges.emplace_back(a, b);
    }
    file.close();
    assert(edges.size() == m);
    Graph graph(0, n, m, edges);

    std::cout << "[FILE: " << file_name << "] "
              << "Running BFS Linear" << std::endl;
    graph.BFS_linear();
    std::cout << "[FILE:" << file_name << "] Running BFS Bag Linear"
              << std::endl;
    graph.BFS_bag_linear();

    for (int i = 0; i < graph.V; i++) {
      if (i % 25 == 0) {
        std::cout << graph.dist_comp[i] << std::endl;
      }
      if (graph.dist_linear[i] != graph.dist_comp[i]) {
        std::cout << "FAILED: " << file_name << std::endl;
        std::cout << i << ": " << graph.dist_linear[i]
                  << " != " << graph.dist_comp[i] << std::endl;
      }
      assert(graph.dist_linear[i] == graph.dist_comp[i]);
    }

    std::cout << "PASSED: " << file_name << std::endl;

  } else {
    std::cout << "Unable to open file" << std::endl;
  }
}

auto main() -> int
{
  read_file_and_exec(file_mini_test);
  read_file_and_exec(file_small_test);
  read_file_and_exec(file_med_test);
  read_file_and_exec(file_large_test);
  read_file_and_exec(file_huge_test);
  read_file_and_exec(file_graph500_small_test);
  return 0;
}