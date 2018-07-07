
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(libsndfile DEFAULT_MSG LIBSNDFILE_INCLUDE_DIR LIBSNDFILE_LIBRARY)

set(LIBSNDFILE_INCLUDE_DIRS ${LIBSNDFILE_INCLUDE_DIR})
set(LIBSNDFILE_LIBRARIES ${LIBSNDFILE_LIBRARY})

add_library(libsndfile INTERFACE)
target_include_directories(libsndfile INTERFACE ${LIBSNDFILE_INCLUDE_DIRS})
target_link_libraries(libsndfile INTERFACE ${LIBSNDFILE_LIBRARIES})
