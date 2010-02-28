set( CURVILINEAR_TESTING_FILEPATH
  ${CURVILINEAR_SCAN_CONVERT_SOURCE_DIR}/Testing/Data/Input/VisualSonics/us_uniform_phantom_w_surface.nrrd
  )

include_directories( ${CURVILINEAR_SCAN_CONVERT_SOURCE_DIR}/Code )

add_executable( curvilinear-scan-convert
  curvilinear-scan-convert-test.cxx
  )
# gdb-pretty http://gitorious.com/gdb-pretty
add_custom_command (TARGET curvilinear-scan-convert
  POST_BUILD
  COMMAND cmake -E copy
  ${CMAKE_CURRENT_SOURCE_DIR}/curvilinear-scan-convert-gdb.py
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
  )
target_link_libraries( curvilinear-scan-convert
  ${VISUALSONICS_LIBRARY}
  ITKStatistics
  ITKCommon
  ITKIO
  )
add_test( curvilinear-scan-convert
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/curvilinear-scan-convert
  ${CURVILINEAR_TESTING_FILEPATH}
  curvilinear-scan-convert_output.mhd
  )

