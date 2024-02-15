#include <iostream>

#ifndef LOCAL_MAKE
#  include <graph.hpp>
#  include <instrumentation.hpp>
#else
#  include "graph.hpp"
#  include "instrumentation.hpp"
#endif

#define LINEAR
#define OPENMP
#define PENANTS

auto main() -> int
{
  std::cin.tie(0);
  int n, m;
  std::cin >> n >> m;
  Graph graph(0, n, m);
  BENCHMARK_BEGIN(build_graph);
  build_graph(graph);
  BENCHMARK_END(build_graph);

  BENCHMARK_BEGIN(linear_bfs);
  graph.BFS_linear();
  BENCHMARK_END(linear_bfs);

  BENCHMARK_BEGIN(bag_linear);
  graph.BFS_bag_linear();
  BENCHMARK_END(bag_linear);

  BENCHMARK_BEGIN(parallel_bag);
  graph.BFS_bag(14);
  BENCHMARK_END(parallel_bag);

  for (int i = 0; i < graph.V; i++) {
    assert(graph.dist_linear[i] == graph.dist_comp[i]);
  }
  std::cout << "Done" << std::endl;
  return 0;
}