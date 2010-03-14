cmake_minimum_required( VERSION 2.8 )
cmake_policy(VERSION 2.8)
# If all the submodules are installed and 'git submodule init && git submodule
# update --recursive' is not called.
cmake_policy( SET CMP0014 OLD )


project( CURVILINEAR_SCAN_CONVERT )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

# itkStreamingResampleImageFilter
find_path( STREAMING_RESAMPLE_IMAGE_FILTER
  itkStreamingResampleImageFilter.h
  PATHS
  ${CMAKE_CURRENT_SOURCE_DIR}/Submodules/itkStreamingResampleImageFilter/Code
  ${ITK_INSTALL_PREFIX}/include/InsightToolkit/BasicFilters
  )
mark_as_advanced( STREAMING_RESAMPLE_IMAGE_FILTER )
if( NOT STREAMING_RESAMPLE_IMAGE_FILTER )
  message( SEND_ERROR "The itkStreamingResampleImageFilter must be available.
  Try `git submodule init` and `git submodule update`." )
endif()
include_directories( ${STREAMING_RESAMPLE_IMAGE_FILTER} )
add_subdirectory( Submodules/itkStreamingResampleImageFilter )


if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -fno-inline")

  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG -ffast-math")

  set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -g")
  set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -O")
endif(CMAKE_COMPILER_IS_GNUCXX)

# where all the executables go
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${CURVILINEAR_SCAN_CONVERT_BINARY_DIR}/bin )

add_subdirectory( Code )

include(CTest)
if(BUILD_TESTING)
  if(NOT EXISTS ${CURVILINEAR_SCAN_CONVERT_SOURCE_DIR}/Testing/Data/Input/VisualSonics/.git)
    message(SEND_ERROR "In order to run tests, the tests/data must be downloaded.  
    If you do not want to run tests, turn BUILD_TESTING OFF.")
  endif()
  enable_testing()
  add_subdirectory(Testing)
endif(BUILD_TESTING)
