# Distributed under the MIT License.
# See LICENSE.txt for details.

set(LIBRARY IrrotationalBnsBoundaryConditions)

add_spectre_library(${LIBRARY})

spectre_target_sources(
  ${LIBRARY}
  PRIVATE
  StarSurface.cpp
  )

spectre_target_headers(
  ${LIBRARY}
  INCLUDE_DIRECTORY ${CMAKE_SOURCE_DIR}/src
  HEADERS
  Factory.hpp
  StarSurface.hpp
  )

target_link_libraries(
  ${LIBRARY}
  PUBLIC
  DataStructures
  Elliptic
  Options
  Parallel
  Utilities
  )
