add_executable(
    makedataset
    main.cpp
    Window.h
    Window.cpp
    Dataset.h
    Dataset.cpp
)

target_link_libraries(makedataset PUBLIC PortAudio libsndfile Vimba Qt5::Widgets)
