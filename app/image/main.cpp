#include <memory>
#include <iostream>
#include <QApplication>
#include "Dataset.h"
#include "Window.h"

int main(int num_args, char** args)
{
    QApplication app(num_args, args);

    if(num_args != 2)
    {
        std::cout << "usage : " << args[0] << " PATH/TO/SOME/DIRECTORY" << std::endl;
        return 1;
    }

    std::shared_ptr<Dataset> dataset = std::make_shared<Dataset>();

    if( dataset->init(args[1]) == false )
    {
        std::cout << "Path not found." << std::endl;
        return 1;
    }

    Window* w = new Window(dataset);

    w->show();

    const int ret = app.exec();

    return ret;
}
