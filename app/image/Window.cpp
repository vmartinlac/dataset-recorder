#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QLabel>
#include <iostream>
#include "Window.h"

Window::Window(
    std::shared_ptr<Dataset> dataset,
    QWidget* parent) :
    _dataset(std::move(dataset)),
    QWidget(parent)
{
    _wtext = new QPlainTextEdit();
    _wtext->setReadOnly(true);

    QHBoxLayout* lay = new QHBoxLayout();
    lay->addWidget(_wtext);

    setLayout(lay);
    setWindowTitle("Make an image dataset");

    refreshStats();
}

void Window::refreshStats()
{
    QString txt;

    int total = 0;
    int index = 1;

    txt += "Project path : " + _dataset->getPath() + "\n";
    txt += "\n";

    txt += "Categories :\n";
    for( Category& c : _dataset->getCategories() )
    {
        txt += "[" + QString::number(index) + "] ";
        txt += c.getName();
        txt += " (" + QString::number(c.getNumSamples()) + " samples )\n";
        index++;
    }

    txt += "\n";
    txt += "Total : " + QString::number(total) + " samples.";

    _wtext->setPlainText(txt);
}
