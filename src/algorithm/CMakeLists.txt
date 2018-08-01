file (GLOB SRC "*.cc")

add_library (algorithm ${SRC})
target_include_directories (algorithm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})