set(EXE_NAME Tests)
file(GLOB_RECURSE ${EXE_NAME}_SRC
  src/*.cc
)
add_executable(${EXE_NAME}
  ${${EXE_NAME}_SRC}
)

target_link_libraries(${EXE_NAME} PRIVATE
  Model
  gtest
)


