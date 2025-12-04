add_executable(2025_day4
  day4.cpp
)

add_test(
  NAME 2025_day4_run1
  COMMAND
    2025_day4 $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.txt> $<SHELL_PATH:${CMAKE_CURRENT_BINARY_DIR}/result1.txt>
)

add_test(
  NAME 2025_day4_test1
  COMMAND
    ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/result1.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/expected1.txt
)
