# Distributed under the MIT License.
# See LICENSE.txt for details.

set(LIBRARY "Test_DataStructures")

set(LIBRARY_SOURCES
  Test_ApplyMatrices.cpp
  Test_BlazeInteroperability.cpp
  Test_CachedTempBuffer.cpp
  Test_ComplexDataVector.cpp
  Test_ComplexDataVectorBinaryOperations.cpp
  Test_ComplexDiagonalModalOperator.cpp
  Test_ComplexModalVector.cpp
  Test_ComplexModalVectorInhomogeneousOperations.cpp
  Test_DataVector.cpp
  Test_DataVectorBinaryOperations.cpp
  Test_DiagonalModalOperator.cpp
  Test_DynamicBuffer.cpp
  Test_ExtractPoint.cpp
  Test_FixedHashMap.cpp
  Test_FloatingPointType.cpp
  Test_IdPair.cpp
  Test_Index.cpp
  Test_IndexIterator.cpp
  Test_LeviCivitaIterator.cpp
  Test_LinkedMessageId.cpp
  Test_LinkedMessageQueue.cpp
  Test_MathWrapper.cpp
  Test_ModalVector.cpp
  Test_ModalVectorInhomogeneousOperations.cpp
  Test_MoreComplexDiagonalModalOperatorMath.cpp
  Test_MoreDiagonalModalOperatorMath.cpp
  Test_NonZeroStaticSizeVector.cpp
  Test_SliceIterator.cpp
  Test_SliceTensorToVariables.cpp
  Test_SliceVariables.cpp
  Test_SpinWeighted.cpp
  Test_StaticDeque.cpp
  Test_StripeIterator.cpp
  Test_TaggedContainers.cpp
  Test_Tags.cpp
  Test_TempBuffer.cpp
  Test_Transpose.cpp
  Test_Variables.cpp
  Test_VectorImpl.cpp
  Test_VectorImplTestHelper.cpp
  )

add_subdirectory(DataBox)
add_subdirectory(Tensor)

add_test_library(${LIBRARY} "${LIBRARY_SOURCES}")

target_link_libraries(
  ${LIBRARY}
  PRIVATE
  DataStructures
  DataStructuresHelpers
  Domain
  Options
  Utilities
  )

# [example_add_pybindings_test]
spectre_add_python_bindings_test(
  "Unit.DataStructures.Python.DataVector"
  Test_DataVector.py
  "Unit;DataStructures;Python"
  PyDataStructures)
# [example_add_pybindings_test]
spectre_add_python_bindings_test(
  "Unit.DataStructures.Python.Matrix"
  Test_Matrix.py
  "Unit;DataStructures;Python"
  PyDataStructures)
spectre_add_python_bindings_test(
  "Unit.DataStructures.Python.ModalVector"
  Test_ModalVector.py
  "Unit;DataStructures;Python"
  PyDataStructures)
