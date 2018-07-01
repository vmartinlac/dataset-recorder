#include <iostream>
#include <opencv2/opencv.hpp>
#include "Window.h"

Window::Window(QWidget* parent) :
    QWidget(parent)
{
    setWindowTitle("Make an image dataset");
}
