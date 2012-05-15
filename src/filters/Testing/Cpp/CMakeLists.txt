#
# Tests for the filters:
# Enable the build of the test binaries by turning BUILD_TESTING on in CMake.
#

include(CTest)

# add_filter_test( TestMyFilter ):
#   -> add_target( TestMyFilter TestMyFilter.cpp )
#   -> link_target( TestMyFilter ${QT_LIBS} ${OpenCV_LIBS} )
#   -> set_target_properties( destinationfolder ${BUILD_DIR}/Testing )
#   -> add_test( TestMyFilter TestMyFilter )
