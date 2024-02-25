set(LIB_NAME Model)
file(GLOB_RECURSE ${LIB_NAME}_SRC
  src/*.cc
)
file(GLOB_RECURSE ${LIB_NAME}_HEADERS
  include/*.h
)
add_library(${LIB_NAME}
  ${${LIB_NAME}_SRC}
  ${${LIB_NAME}_HEADERS}
)

target_include_directories(${LIB_NAME} PUBLIC ./include)


