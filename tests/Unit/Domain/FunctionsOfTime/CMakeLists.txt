# Distributed under the MIT License.
# See LICENSE.txt for details.

set(LIBRARY "Test_FunctionsOfTime")

set(LIBRARY_SOURCES
  Test_FixedSpeedCubic.cpp
  Test_FunctionsOfTimeAreReady.cpp
  Test_IntegratedFunctionOfTime.cpp
  Test_ThreadsafeList.cpp
  Test_OutputTimeBounds.cpp
  Test_PiecewisePolynomial.cpp
  Test_QuaternionFunctionOfTime.cpp
  Test_QuaternionHelpers.cpp
  Test_SettleToConstant.cpp
  Test_SettleToConstantQuaternion.cpp
  Test_Tags.cpp
  )

add_test_library(${LIBRARY} "${LIBRARY_SOURCES}")

target_link_libraries(
  ${LIBRARY}
  PRIVATE
  Actions
  DataStructures
  DomainCreators
  FunctionsOfTime
  H5
  Informer
  Options
  SerializationHelpers
  Utilities
  )
