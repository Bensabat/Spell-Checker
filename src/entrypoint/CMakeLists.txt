set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})

add_executable (TextMiningCompiler compiler.cc)
target_link_libraries (TextMiningCompiler LINK_PUBLIC algorithm)

add_executable (TextMiningApp spellchecker.cc)
target_link_libraries (TextMiningApp LINK_PUBLIC algorithm)