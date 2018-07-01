add_executable(
    make-image-dataset
    main.cpp
    Window.h
    Window.cpp
    Dataset.h
    Dataset.cpp
)

target_link_libraries(make-image-dataset PUBLIC opencv_core Qt5::Widgets)
