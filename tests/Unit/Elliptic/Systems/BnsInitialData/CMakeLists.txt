# Distributed under the MIT License.
# See LICENSE.txt for details.

set(LIBRARY "Test_BnsInitialData")

set(LIBRARY_SOURCES
  Test_Equations.cpp
  Test_Tags.cpp
  )

add_test_library(${LIBRARY} "${LIBRARY_SOURCES}")

target_link_libraries(
  ${LIBRARY}
  PRIVATE
  DataStructures
  DataStructuresHelpers
  EllipticTestHelpers
  BnsInitialData
  Utilities
  )

add_subdirectory(BoundaryConditions)
