# Distributed under the MIT License.
# See LICENSE.txt for details.

set(LIBRARY "Test_XctsBoundaryConditions")

set(LIBRARY_SOURCES
  Test_ApparentHorizon.cpp
  Test_Flatness.cpp
  Test_Robin.cpp
  )

add_test_library(${LIBRARY} "${LIBRARY_SOURCES}")

target_link_libraries(
  ${LIBRARY}
  PRIVATE
  CoordinateMaps
  DataStructures
  Domain
  DomainStructure
  Elliptic
  GeneralRelativitySolutions
  LinearOperators
  Utilities
  XctsBoundaryConditions
  XctsSolutions
  )
