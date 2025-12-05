add_executable(2015_day1
  day1.cpp
)

add_test(
  NAME 2015_day1_run1
  COMMAND
    2015_day1 $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.txt> $<SHELL_PATH:${CMAKE_CURRENT_BINARY_DIR}/result1.txt>
)

add_test(
  NAME 2015_day1_test1
  COMMAND
    ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/result1.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/expected1.txt
)

add_test(
  NAME 2015_day1_run2
  COMMAND
    2015_day1 $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/tests/test2.txt> $<SHELL_PATH:${CMAKE_CURRENT_BINARY_DIR}/result2.txt>
)

add_test(
  NAME 2015_day1_test2
  COMMAND
    ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/result2.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/expected2.txt
)
