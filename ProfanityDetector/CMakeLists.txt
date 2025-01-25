# CMakeList.txt : CMake project for ProfanityDetector, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (ProfanityDetector "ProfanityDetector.cpp" "ProfanityDetector.h" "Test.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ProfanityDetector PROPERTY CXX_STANDARD 20)
endif()

find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
  target_link_libraries(ProfanityDetector PRIVATE ZLIB::ZLIB)
else()
  message(FATAL_ERROR "ZLib library not found")
endif()
