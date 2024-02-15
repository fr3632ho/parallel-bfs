#ifndef GRAPH_HPP
#define GRAPH_HPP

/* Includes */
#include <atomic>
#include <iostream>
#include <vector>

constexpr int EDGE_DEGREE = 256;
constexpr int VERTEX_DEGREE = 256;
constexpr int INF = 1 << 29;
constexpr size_t vector_max_size = 1 << 10;

typedef struct edge_t edge_t;

struct edge_t
{
  int a, b;
  edge_t(int a, int b)
      : a {a}
      , b {b}
  {
  }
};

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

  Graph(int m_start,
        int vertices,
        int number_of_edges,
        std::vector<edge_t> edges);

  /**
   * @brief Connect two nodes
   *
   * @param a
   * @param b
   */
  auto connect(const int a, const int b) -> void;

  /**
   * @brief  Linear BFS implementation using unordered_set and deque
   *
   * @return int
   */
  auto BFS_linear() -> int;
  auto BFS_openmp() -> int;
  auto BFS_bag_linear() -> int;
  auto BFS_bag(const size_t number_of_threads) -> int;

  /**
   * @brief Check if the parallel BFS implementation is correct
   *
   * @return int
   */
  auto check() -> int;
  friend auto operator<<(std::ostream& os, const Graph& graph) -> std::ostream&;

  int V, E;
  std::vector<int> dist_linear;
  std::vector<int> dist_comp;
  std::vector<std::vector<int>> adj;

private:
  int start, v, m;
};

auto build_graph(Graph& graph) -> void;
auto operator<<(std::ostream& os, const Graph& graph) -> std::ostream&;

#endif  // GRAPH_HPP