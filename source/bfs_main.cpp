#include <iostream>

#include <graph.hpp>
#include <instrumentation.hpp>

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
  return 0;
}