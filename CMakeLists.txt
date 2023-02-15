cmake_minimum_required(VERSION 3.0.0)
project(HTTP/1.1 VERSION 0.1.0)

include(CTest)
enable_testing()

add_compile_options(-Wextra)

add_executable(HTTP1 main.c session.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
