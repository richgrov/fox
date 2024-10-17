add_executable(fox
  chars.h
  main.c
  operator.c
  operator.h
  preproc.c
  preproc.h
  error.c
  error.h
)

set_property(TARGET fox PROPERTY C_STANDARD 11)
target_include_directories(fox PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_compile_definitions(fox PRIVATE _CRT_SECURE_NO_WARNINGS)
