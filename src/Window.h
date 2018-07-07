#pragma once

#include <QWidget>

class QButtonGroup;
class QListWidget;
class QLineEdit;
class QLabel;
class QGroupBox;

class Window : public QWidget
{
    Q_OBJECT
public:

    Window(QWidget* parent=nullptr);

protected:

    enum
    {
        ID_IMAGE,
        ID_SOUND
    };

protected:

    QLabel* m_dataset_size;
    QLineEdit* m_dataset_path;
    QButtonGroup* m_dataset_kind;

    QListWidget* m_category_list;

    QLineEdit* m_sample_next_filename;
    QLineEdit* m_sample_prefix;
    QLabel* m_sample_category;

protected:

    QGroupBox* create_dataset_groupbox();
    QGroupBox* create_category_groupbox();
    QGroupBox* create_sample_groupbox();
    QGroupBox* create_sensor_groupbox();

protected slots:

    void dataset_apply();
    void dataset_open();
    void dataset_refresh_size();

    void category_add();
    void category_rename();
    void category_remove();
};
