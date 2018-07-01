#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Window.h"

Window::Window(
    std::shared_ptr<Dataset> dataset,
    QWidget* parent) :
    _dataset(std::move(dataset)),
    QWidget(parent)
{
    QLabel* l = new QLabel();
    l->setText("Project path : " + _dataset->getPath() );

    _wtext = new QTextEdit();
    _wtext->setReadOnly(true);

    QHBoxLayout* hl = new QHBoxLayout();
    hl->addWidget(_wtext);

    QVBoxLayout* mainl = new QVBoxLayout();
    mainl->addWidget(l);
    mainl->addLayout(hl);

    setLayout(mainl);
    setWindowTitle("Make an image dataset");
}

void Window::refreshStats()
{
    ;
}
