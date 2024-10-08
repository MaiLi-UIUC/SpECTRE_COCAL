# Distributed under the MIT License.
# See LICENSE.txt for details.

set(LIBRARY ControlSystem)

add_spectre_library(${LIBRARY})

spectre_target_sources(
  ${LIBRARY}
  PRIVATE
  Averager.cpp
  CalculateMeasurementTimescales.cpp
  Controller.cpp
  DataVectorHelpers.cpp
  ExpirationTimes.cpp
  FutureMeasurements.cpp
  TimescaleTuner.cpp
  UpdateFunctionOfTime.cpp
  )

spectre_target_headers(
  ${LIBRARY}
  INCLUDE_DIRECTORY ${CMAKE_SOURCE_DIR}/src
  HEADERS
  Averager.hpp
  CalculateMeasurementTimescales.hpp
  CombinedName.hpp
  Component.hpp
  Controller.hpp
  DataVectorHelpers.hpp
  ExpirationTimes.hpp
  FutureMeasurements.hpp
  IsSize.hpp
  Metafunctions.hpp
  NamespaceDocs.hpp
  RunCallbacks.hpp
  TimescaleTuner.hpp
  Trigger.hpp
  UpdateControlSystem.hpp
  UpdateFunctionOfTime.hpp
  WriteData.hpp
  )

target_link_libraries(
  ${LIBRARY}
  PUBLIC
  ApparentHorizonFinder
  Boost::boost
  DataStructures
  Domain
  DomainStructure
  ErrorHandling
  FiniteDifference
  FunctionsOfTime
  GSL::gsl
  Interpolation
  Logging
  Parallel
  Printf
  Serialization
  Time
  Utilities
  INTERFACE
  Observer
  PRIVATE
  GrSurfaces
  )

add_subdirectory(Actions)
add_subdirectory(ControlErrors)
add_subdirectory(Measurements)
add_subdirectory(Protocols)
add_subdirectory(Systems)
add_subdirectory(Tags)
