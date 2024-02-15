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

  BENCHMARK_BEGIN(parallel_bag);
  graph.BFS_bag(16);
  BENCHMARK_END(parallel_bag);
  std::cout << "Done" << std::endl;
  return 0;
}