#include <memory>
#include <iostream>
#include <QApplication>
#include "Dataset.h"
#include "CameraManager.h"
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

    dataset->init(args[1]);

    std::unique_ptr<CameraManager> cm( new CameraManager() );

    Window* w = new Window(dataset);

    w->show();

    const int ret = app.exec();

    delete w;

    dataset.reset();
    cm.reset();

    return ret;
}
