# Distributed under the MIT License.
# See LICENSE.txt for details.

set(EXECUTABLE ParallelInfo)

set(EXECUTABLE_SOURCES
  ParallelInfo.cpp
  ${EXECUTABLE}.decl.h
  )

add_charm_module(${EXECUTABLE})

add_spectre_executable(
  ${EXECUTABLE}
  EXCLUDE_FROM_ALL
  ${EXECUTABLE_SOURCES}
  )

add_dependencies(
  ${EXECUTABLE}
  module_GlobalCache
  module_ParallelInfo
  )

target_link_libraries(
  ${EXECUTABLE}
  PRIVATE
  Charmxx::main
  ErrorHandling
  Informer
  Printf
  SystemUtilities
  )
