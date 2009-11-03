cmake_minimum_required( VERSION 2.8 )
if( COMMAND cmake_policy )
  cmake_policy( VERSION 2.8 )
endif( COMMAND cmake_policy )


project( CURVILINEAR_SCAN_CONVERT )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

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

add_subdirectory(source)

include(CTest)
if(BUILD_TESTING)
  if(NOT EXISTS ${CURVILINEAR_SCAN_CONVERT_SOURCE_DIR}/tests/data/.git)
    message(SEND_ERROR "In order to run tests, the tests/data must be downloaded.  
    If you do not want to run tests, turn BUILD_TESTING OFF.")
  endif()
  enable_testing()
  add_subdirectory(tests)
endif(BUILD_TESTING)
