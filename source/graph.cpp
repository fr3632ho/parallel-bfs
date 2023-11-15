
#include <cassert>
#include <deque>
#include <iostream>
#include <unordered_set>
#include <utility>

#include <debug.hpp>
#include <graph.hpp>

using std::cin;
using std::cout;
using std::endl;

auto Graph::connect(int a, int b) -> void
{
  adj[a].push_back(b);
  adj[b].push_back(a);
}

auto Graph::BFS_linear() -> int
{
  std::unordered_set<int> vis;
  std::deque<std::pair<int, int>> queue;
  // bag[log(N)] bag;
  vis.reserve(V);

#ifdef VERIFY
  dist_linear.clear();
  dist_linear.resize(V);
#endif  // VERIFY

  queue.emplace_back(start, 0);
  vis.insert(start);

  while (!queue.empty()) {
    auto [k, d] = queue.front();
    queue.pop_front();

#ifdef VERIFY
    dist_linear[k] = d;
#endif  // VERIFY
    for (auto u : adj[k]) {
      if (!vis.count(u)) {
        vis.insert(u);
        queue.emplace_back(u, d + 1);
      }
    }
  }

#ifdef VERIFY
  cout << dist_linear << endl;
#endif

  return EXIT_SUCCESS;
}

auto Graph::BFS_openmp() -> int
{
  return 0;
}

auto build_graph(Graph& graph) -> void
{
  int a, b;
  for (int i = 0; i < graph.E; i++) {
    cin >> a >> b;
    graph.connect(a, b);
  }

  // cout << graph << endl;
}

auto Graph::check() -> int
{
#ifdef VERIFY
  for (size_t i = 0; i < V; i++) {
    assert(dist_linear[i] == dist_comp[i]);
  }
#endif  // VERIFY
  return EXIT_SUCCESS;
}

auto operator<<(std::ostream& os, const Graph& graph) -> std::ostream&
{
  os << "Graph  {\n";
  os << "n = " << graph.adj.size() << "\n";
  for (auto it = graph.adj.begin(); it != graph.adj.end(); it++) {
    os << (it - graph.adj.begin()) << ": [ ";
    for (int it2 : *it) {
      os << it2 << " ";
    }
    os << "]\n";
  }
  os << "}";
  return os;
}
