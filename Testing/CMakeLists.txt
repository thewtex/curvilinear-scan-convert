set( CURVILINEAR_TESTING_FILEPATH
  ${CURVILINEAR_SCAN_CONVERT_SOURCE_DIR}/Testing/Data/Input/VisualSonics/us_uniform_phantom_w_surface.nrrd
  )

include_directories( ${CURVILINEAR_SCAN_CONVERT_SOURCE_DIR}/Code )

add_executable( itkCartesianToRThetaTransformTest
  itkCartesianToRThetaTransformTest.cxx
  )
# gdb-pretty http://gitorious.com/gdb-pretty
add_custom_command (TARGET itkCartesianToRThetaTransformTest
  POST_BUILD
  COMMAND cmake -E copy
  ${CMAKE_CURRENT_SOURCE_DIR}/itkCartesianToRThetaTransformTest-gdb.py
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
  )
target_link_libraries( itkCartesianToRThetaTransformTest
  ${VISUALSONICS_LIBRARY}
  ITKStatistics
  ITKCommon
  ITKIO
  )
add_test( itkCartesianToRThetaTransformTest
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/itkCartesianToRThetaTransformTest
  ${CURVILINEAR_TESTING_FILEPATH}
  itkCartesianToRThetaTransformTestOutput.mhd
  )

