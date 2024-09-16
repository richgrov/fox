add_executable(fox
  main.c
  operator.c
  operator.h
  preproc.c
  preproc.h
  error.c
  error.h
)

set_property(TARGET fox PROPERTY C_STANDARD 11)
target_compile_definitions(fox PRIVATE _CRT_SECURE_NO_WARNINGS)
