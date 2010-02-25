set( CURVILINEAR_TESTING_FILEPATH
  ${CURVILINEAR_SCAN_CONVERT_SOURCE_DIR}/Testing/Data/Input/VisualSonics/us_uniform_phantom_w_surface.nrrd
  )

include_directories( ${CURVILINEAR_SCAN_CONVERT_SOURCE_DIR}/Code )

add_executable( curvilinear-scan-convert
  curvilinear-scan-convert-test.cxx
  )
target_link_libraries( curvilinear-scan-convert
  ${VISUALSONICS_LIBRARY}
  ITKStatistics
  )
add_test( curvilinear-scan-convert
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/curvilinear-scan-convert
  ${CURVILINEAR_TESTING_FILEPATH}
  curvilinear-scan-convert_output.mhd
  )

