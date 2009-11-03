set( CURVILINEAR_TESTING_FILEPATH
  ${CURVILINEAR_SCAN_CONVERT_SOURCE_DIR}/tests/data/machine/visualsonics/vevo770/rmv710b/pat143_seg2.rdi
  )


find_path( BMODE_INCLUDE
  NAMES itkBModeImageFilter.h
  )
if( BMODE_INCLUDE-NOTFOUND )
  message( SEND_ERROR "The itkBModeImageFilter.h header location must be
  specified." )
endif()
include_directories( ${BMODE_INCLUDE} )

find_path( VISUALSONICS_INCLUDE
  NAMES itkVisualSonicsImageIO.h
  )
if( VISUALSONICS_INCLUDE-NOTFOUND )
  message( SEND_ERROR "The itkVisualSonicsImageIO.h header location must be
  specified." )
endif()
include_directories( ${VISUALSONICS_INCLUDE} )

include_directories( ${CURVILINEAR_SCAN_CONVERT_SOURCE_DIR}/source )

set_source_files_properties(
  curvilinear-b-mode.cxx
  PROPERTIES COMPILE_FLAGS -DITK_MANUAL_INSTANTIATION
  )
add_executable( curvilinear-b-mode
  curvilinear-b-mode.cxx
  b-mode-instan.cxx
  reader-instan.cxx
  writer-instan.cxx
  )
target_link_libraries( curvilinear-b-mode
  ITKVisualSonicsImageIO
  ITKStatistics
  )
add_test( curvilinear-b-mode
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/curvilinear-b-mode
  ${CURVILINEAR_TESTING_FILEPATH}
  curvilinear-b-mode_output.mhd
  )

