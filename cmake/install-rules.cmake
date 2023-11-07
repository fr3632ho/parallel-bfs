install(
    TARGETS parallel-bfs_exe
    RUNTIME COMPONENT parallel-bfs_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
