add_executable(
    make-image-dataset
    main.cpp
    Window.h
    Window.cpp
    Dataset.h
    Dataset.cpp
    CameraManager.h
    CameraManager.cpp
)

target_link_libraries(make-image-dataset PUBLIC Vimba Qt5::Widgets)
