#pragma once

/* Includes */
#include <iostream>
#include <vector>

#define VERIFY

constexpr int EDGE_DEGREE = 256;
constexpr int VERTEX_DEGREE = 256;

typedef struct edge_t edge_t;

class Graph
{
public:
  Graph(int strt, int vertices, int edges)
      : start {strt}
      , V {vertices}
      , E {edges}
  {
    adj.resize(static_cast<size_t>(vertices));
  }

  /**
   * @brief Connect two nodes
   *
   * @param a
   * @param b
   */
  auto connect(int a, int b) -> void;

  /**
   * @brief  Linear BFS implementation using unordered_set and deque
   *
   * @return int
   */
  auto BFS_linear() -> int;
  auto BFS_openmp() -> int;

  /**
   * @brief Check if the parallel BFS implementation is correct
   *
   * @return int
   */
  auto check() -> int;
  friend auto operator<<(std::ostream& os, const Graph& graph) -> std::ostream&;

  int V, E;

private:
  std::vector<std::vector<int>> adj;
  int start, v, m;
#ifdef VERIFY
  std::vector<int> dist_linear;
  std::vector<int> dist_comp;
#endif  // VERIFY
};

auto build_graph(Graph& graph) -> void;
auto operator<<(std::ostream& os, const Graph& graph) -> std::ostream&;