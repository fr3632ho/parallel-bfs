#pragma once

#include <iostream>
#include <iterator>
#include <utility>

#define LOGF(...) \
  do { \
    fprintf(stderr, __VA_ARGS__); \
  } while (0)

void LOG()
{
  std::cout << std::endl;
}

template<typename First, typename... Rest>
void LOG(First&& first, Rest&&... rest)
{
  std::cout << std::forward<First>(first) << " ";
  LOG(std::forward<Rest>(rest)...);
}

template<class Stream,
         class Vector,
         class Begin = decltype(std::begin(std::declval<Vector>()))>
inline Stream& operator<<(Stream& stream, const Vector& vect)
{
  stream << "[";
  const char* dlm = "";
  for (const auto& i : vect) {
    stream << dlm << i;
    dlm = ", ";
  }
  stream << "]\n";
  return stream;
}