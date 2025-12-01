add_executable(day1
  day1.cpp
)

add_test(
  NAME day1_reset
  COMMAND
    ${CMAKE_COMMAND} -E rm -f ${CMAKE_CURRENT_BINARY_DIR}/result.txt
)

add_test(
  NAME day1_run
  COMMAND
    day1 $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/test.txt> $<SHELL_PATH:${CMAKE_CURRENT_BINARY_DIR}/result.txt>
)

add_test(
  NAME day1_test
  COMMAND
    ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/result.txt ${CMAKE_CURRENT_SOURCE_DIR}/expected.txt
)
