# Distributed under the MIT License.
# See LICENSE.txt for details.

set(LIBRARY XctsBoundaryConditions)

add_spectre_library(${LIBRARY})

spectre_target_sources(
  ${LIBRARY}
  PRIVATE
  ApparentHorizon.cpp
  Flatness.cpp
  Robin.cpp
  )

spectre_target_headers(
  ${LIBRARY}
  INCLUDE_DIRECTORY ${CMAKE_SOURCE_DIR}/src
  HEADERS
  ApparentHorizon.hpp
  Factory.hpp
  Flatness.hpp
  Robin.hpp
  )

target_link_libraries(
  ${LIBRARY}
  PUBLIC
  DataStructures
  Domain
  Elliptic
  ErrorHandling
  XctsSolutions
  Options
  Serialization
  Utilities
  )
