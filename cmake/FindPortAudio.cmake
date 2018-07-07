include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PortAudio DEFAULT_MSG PORTAUDIO_INCLUDE_DIR PORTAUDIO_LIBRARY)

set(PORTAUDIO_INCLUDE_DIRS ${PORTAUDIO_INCLUDE_DIR})
set(PORTAUDIO_LIBRARIES ${PORTAUDIO_LIBRARY})

add_library(PortAudio INTERFACE)
target_include_directories(PortAudio INTERFACE ${PORTAUDIO_INCLUDE_DIRS})
target_link_libraries(PortAudio INTERFACE ${PORTAUDIO_LIBRARIES})
