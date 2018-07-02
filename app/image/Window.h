#pragma once

#include <memory>
#include <QWidget>
#include "Dataset.h"

class QLineEdit;
class QPlainTextEdit;

class Window : public QWidget
{
    Q_OBJECT

public:

    Window(
        std::shared_ptr<Dataset> dataset,
        QWidget* parent=nullptr);

protected slots:

    void refreshStats();

protected:

    std::shared_ptr<Dataset> _dataset;
    QPlainTextEdit* _wtext;
};
