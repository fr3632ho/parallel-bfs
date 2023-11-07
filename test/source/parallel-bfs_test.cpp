#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "parallel-bfs" ? 0 : 1;
}
