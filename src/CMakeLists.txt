set (CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17")
set (CMAKE_CXX_FLAGS_DEBUG "-g")

include_directories (.)

add_subdirectory (algorithm)
add_subdirectory (entrypoint)