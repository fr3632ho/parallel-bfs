
#include <cassert>
#include <chrono>
#include <deque>
#include <iostream>
#include <thread>
#include <unordered_set>
#include <utility>

#include <pthread.h>

#ifndef LOCAL_MAKE
#  include <bag.hpp>
#  include <graph.hpp>
#  define LOGF(...)

#else
#  include "bag.hpp"
#  include "debug.hpp"
#  include "graph.hpp"
#endif  // LOCAL_MAKE

using std::cin;
using std::cout;
using std::endl;

extern auto clear_thread_data() -> void;
extern auto alloc_bag(size_t size) -> bag_t*;

Graph::Graph(int m_start,
             int v_vertices,
             int m_edges,
             std::vector<edge_t> edges)
    : start {m_start}
    , V {v_vertices}
    , E {m_edges}
{
  adj.resize(static_cast<size_t>(v_vertices));
  for (auto& e : edges) {
    connect(e.a, e.b);
  }
}

auto Graph::connect(const int a, const int b) -> void
{
  adj[a].emplace_back(b);
  adj[b].emplace_back(a);
}

auto Graph::BFS_linear() -> int
{
  std::deque<std::pair<int, int>> queue;
  dist_linear.clear();
  dist_linear.resize(V);
  std::fill(dist_linear.begin(), dist_linear.end(), INF);
  dist_linear[start] = 0;

  queue.emplace_back(start, 0);

  while (!queue.empty()) {
    auto [k, d] = queue.front();
    queue.pop_front();

    for (auto u : adj[k]) {
      if (dist_linear[u] == INF) {
        dist_linear[u] = dist_linear[k] + 1;
        queue.emplace_back(u, d + 1);
      }
    }
  }

  return EXIT_SUCCESS;
}

auto Graph::BFS_openmp() -> int
{
  return 0;
}

auto Graph::BFS_bag_linear() -> int
{
  dist_comp.resize(V);
  std::fill(dist_comp.begin(), dist_comp.end(), INF);

  bag_t layer_one(V + 1), layer_two(V + 1);
  layer_one.insert(start);
  dist_comp[start] = 0;
  bool changed = false;
  do {
    changed = false;
    pennant_t* temp;
    for (int i = 0; i < layer_one.size; i++) {
      // check if pennant is empty
      if (layer_one.arr[i] == nullptr) {
        continue;
      }

      temp = layer_one.arr[i];
      for (auto& u : *temp) {
        // u will have distance set. Loop through neigbours and explore graph
        for (auto& v : adj[u]) {
          if (dist_comp[v] == INF) {
            dist_comp[v] = dist_comp[u] + 1;
            layer_two.insert(v);
            changed = true;
          }
        }
      }

      delete temp;
      layer_one.arr[i] = nullptr;
    }
    if (changed) {
      layer_one.merge(&layer_two);
    }
  } while (changed);

  return EXIT_SUCCESS;
}

typedef struct thread_data_t thread_data_t;
pthread_barrier_t barrier;
std::atomic<int> dist_bag_parallel[vector_max_size];

struct thread_data_t
{
  Graph* graph;
  bool merge_updated;
  bag_t* assign_bag;  // the assign bag of thread[0] will be the 'collect' bag
  bag_t* merge_bag;
};

static thread_data_t data[16];

typedef struct thread_in_t thread_int_t;
struct thread_in_t
{
  int thread_id;
};

std::atomic<bool> terminate = false;

auto thread_func(void* args) -> void*
{
  // thread_data_t* d = (static_cast<thread_data_t*>(args));
  thread_in_t* d = (static_cast<thread_in_t*>(args));
  int thread_id = d->thread_id;
  Graph* graph = data[thread_id].graph;
  int inf_check = INF;
  int curr_dist = 2;
  // LOGF("[%d]: Thread started\n", thread_id);
  while (1) {
    pthread_barrier_wait(&barrier);
    data[thread_id].merge_updated = false;

    if (terminate.load()) {
      break;  // only break point for threads
    }

    pennant_t* temp;
    bool success_cas;
    for (int i = 0; i < data[thread_id].assign_bag->size; i++) {
      // check if pennant is empty

      if (data[thread_id].assign_bag->arr[i] == nullptr) {
        continue;
      }

      temp = data[thread_id].assign_bag->arr[i];

      for (auto& u : *temp) {
        for (auto& v : graph->adj[u]) {
          int next_dist = dist_bag_parallel[v].load(std::memory_order_acquire);

          if (next_dist == inf_check) {
            success_cas = true;
            do {
              if (dist_bag_parallel[v].load() != inf_check) {
                success_cas = false;
                break;
              }
            } while (!dist_bag_parallel[v].compare_exchange_weak(inf_check,
                                                                 curr_dist));
            if (success_cas) {
              data[thread_id].merge_bag->insert(v);
            }
          }
        }
        data[thread_id].assign_bag->arr[i] = nullptr;
      }
    }

    if (data[thread_id].merge_bag->number_of_elements > 0) {
      data[thread_id].merge_updated = true;
    }
    curr_dist++;

    pthread_barrier_wait(&barrier);
  }

  // LOGF("thread %d exiting\n", thread_id);
  // CLEAR THREAD DATA
  // std::cout << "clear_thread_data[" << thread_id << "]" << std::endl;
  clear_thread_data();
  return nullptr;
}

auto split_thread_data(size_t low, size_t high) -> void
{
  if (low == high) {
    return;
  }

  size_t mid = (low + high) / 2;
  data[low].assign_bag->split(data[mid + 1].assign_bag);
  split_thread_data(low, mid);
  split_thread_data(mid + 1, high);
}

auto merge_thread_data(const size_t number_of_threads) -> void
{
  for (int i = 0; i < number_of_threads; i++) {
    // memset(data[i].assign_bag;
    std::memset(data[i].assign_bag->arr, 0, data[i].assign_bag->size);
  }

  for (size_t i = 0; i < number_of_threads; i++) {
    data[0].assign_bag->merge(data[i].merge_bag);
  }
}

auto Graph::BFS_bag(const size_t number_of_threads) -> int
{
  // LOGF("[MAIN] starting BFS\n");
  for (size_t i = 0; i < V; i++) {
    dist_bag_parallel[i].store(INF);
  }

  pthread_barrier_init(&barrier, nullptr, number_of_threads + 1);

  pthread_t threads[number_of_threads];
  thread_in_t input_data[number_of_threads];
  for (int i = 0; i < number_of_threads; i++) {
    input_data[i].thread_id = i;

    data[i].assign_bag = alloc_bag(V + 1);
    data[i].merge_bag = alloc_bag(V + 1);
    data[i].merge_updated = false;
    data[i].graph = this;
  }
  // initial search from start
  dist_bag_parallel[start].store(0);
  for (auto& u : adj[start]) {
    data[0].assign_bag->insert(u);
    dist_bag_parallel[u].store(1);
  }

  // LOGF("[MAIN] starting threads\n");
  for (size_t i = 0; i < number_of_threads; i++) {
    pthread_create(&threads[i], nullptr, thread_func, &input_data[i]);
  }

  // LOGF("[MAIN] threads started, entering main loop\n");
  data[0].assign_bag->display_bag_in_binary();

  bool not_terminated = true;
  int iter = 0;
  do {
    split_thread_data(0, number_of_threads - 1);
    pthread_barrier_wait(&barrier);
    pthread_barrier_wait(&barrier);

    not_terminated = false;
    for (size_t i = 0; i < number_of_threads; i++) {
      not_terminated |= data[i].merge_updated;
    }
    if (!not_terminated)
      break;

    merge_thread_data(number_of_threads);
  } while (not_terminated);

  terminate.store(true);

  // LOGF("[MAIN] terminating threads, exit true, now waiting\n");
  pthread_barrier_wait(&barrier);

  for (int index = 0; index < number_of_threads; index++) {
    pthread_join(threads[index], nullptr);
  }

  clear_thread_data();

  // LOGF("[MAIN] exiting\n");
  for (int i = 0; i < V; i++) {
    // assert(dist_linear[i] == dist_bag_parallel[i].load());
  }

  return EXIT_SUCCESS;
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
  for (size_t i = 0; i < V; i++) {
    assert(dist_linear[i] == dist_comp[i]);
  }
  return EXIT_SUCCESS;
}

auto operator<<(std::ostream& os, const Graph& graph) -> std::ostream&
{
  os << "Graph  {\n";
  os << "n = " << graph.adj.size() << " m = " << graph.E << ""
     << "\n";
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
