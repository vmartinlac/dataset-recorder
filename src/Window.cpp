#include <QLabel>
#include <QGridLayout>
#include <QButtonGroup>
#include <QStackedLayout>
#include <QToolBar>
#include <QListWidget>
#include <QRadioButton>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include "Window.h"

QGroupBox* Window::create_dataset_groupbox()
{
    QFormLayout* form_dataset = new QFormLayout();
    QGroupBox* grp_dataset = new QGroupBox();
    QHBoxLayout* dataset_path_layout = new QHBoxLayout();
    QLineEdit* dataset_path = new QLineEdit();
    QPushButton* dataset_open_btn = new QPushButton("Open");
    QWidget* dataset_path_widget = new QWidget();
    QRadioButton* dataset_image = new QRadioButton("Image");
    QRadioButton* dataset_sound = new QRadioButton("Sound");
    QButtonGroup* dataset_kind_group = new QButtonGroup();
    QHBoxLayout* dataset_kind_layout = new QHBoxLayout();
    QLabel* dataset_size = new QLabel("N/A");
    QPushButton* dataset_apply_btn = new QPushButton("Apply");

    dataset_path->setReadOnly(true);
    dataset_sound->setChecked(true);
    dataset_kind_group->addButton(dataset_image, ID_IMAGE);
    dataset_kind_group->addButton(dataset_sound, ID_SOUND);
    dataset_path_layout->addWidget(dataset_path, 1);
    dataset_path_layout->addWidget(dataset_open_btn, 0);
    dataset_path_widget->setLayout(dataset_path_layout);
    dataset_kind_layout->addWidget(dataset_image);
    dataset_kind_layout->addWidget(dataset_sound);
    form_dataset->addRow("Path :", dataset_path_widget);
    form_dataset->addRow("Kind :", dataset_kind_layout);
    form_dataset->addRow("Size :", dataset_size);
    form_dataset->addRow(dataset_apply_btn);
    grp_dataset->setLayout(form_dataset);
    grp_dataset->setTitle("Dataset");

    m_dataset_size = dataset_size;
    m_dataset_kind = dataset_kind_group;
    m_dataset_path = dataset_path;

    connect(dataset_apply_btn, &QPushButton::clicked, this, &Window::dataset_apply);
    connect(dataset_open_btn, &QPushButton::clicked, this, &Window::dataset_open);

    return grp_dataset;
}

QGroupBox* Window::create_category_groupbox()
{
    QGroupBox* category_groupbox = new QGroupBox();
    QListWidget* category_list = new QListWidget();
    QHBoxLayout* category_main_layout = new QHBoxLayout();
    QToolBar* category_toolbar = new QToolBar();
    QAction* category_add = category_toolbar->addAction("Add");
    QAction* category_rename = category_toolbar->addAction("Rename");
    QAction* category_remove = category_toolbar->addAction("Remove");

    category_toolbar->setOrientation(Qt::Vertical);
    category_main_layout->addWidget(category_list);
    category_main_layout->addWidget(category_toolbar);
    category_groupbox->setTitle("Category");
    category_groupbox->setLayout(category_main_layout);

    m_category_list = category_list;

    connect( category_add, &QAction::triggered, this, &Window::category_add);
    connect( category_rename, &QAction::triggered, this, &Window::category_rename);
    connect( category_remove, &QAction::triggered, this, &Window::category_remove);

    return category_groupbox;
}

QGroupBox* Window::create_sample_groupbox()
{
    QGroupBox* sample_groupbox = new QGroupBox();
    QVBoxLayout* sample_layout = new QVBoxLayout();
    QFormLayout* sample_form = new QFormLayout();
    QLineEdit* sample_prefix = new QLineEdit();
    QLineEdit* sample_next_filename = new QLineEdit();
    QLabel* sample_category = new QLabel("N/A");
    QStackedLayout* sample_stacked_layout = new QStackedLayout();

    sample_next_filename->setReadOnly(true);
    sample_form->addRow("Prefix :", sample_prefix);
    sample_form->addRow("Next file name :", sample_next_filename);
    sample_form->addRow("Category :", sample_category);
    sample_layout->addLayout(sample_form);
    sample_layout->addLayout(sample_stacked_layout);
    sample_groupbox->setLayout(sample_layout);
    sample_groupbox->setTitle("Sample");

    return sample_groupbox;
}

QGroupBox* Window::create_sensor_groupbox()
{
    QGroupBox* sensor_groupbox = new QGroupBox();
    QStackedLayout* sensor_stackedlayout = new QStackedLayout();

    sensor_groupbox->setTitle("Sensor");
    sensor_groupbox->setLayout(sensor_stackedlayout);

    sensor_stackedlayout->addWidget( new QLabel("rien") );

    return sensor_groupbox;
}

Window::Window(QWidget* parent) : QWidget(parent)
{
    QGridLayout* l = new QGridLayout();
    l->addWidget(create_dataset_groupbox(), 0, 0);
    l->addWidget(create_category_groupbox(), 1, 0);
    l->addWidget(create_sample_groupbox(), 2, 0);
    l->addWidget(create_sensor_groupbox(), 0, 1, 3, 1);

    /*
    QVBoxLayout* main_layout = new QVBoxLayout();
    main_layout->addWidget(create_dataset_groupbox());
    main_layout->addWidget(create_category_groupbox());
    main_layout->addWidget(create_sample_groupbox());
    main_layout->addWidget(create_sensor_groupbox());
    */

    setLayout(l);
    setWindowTitle("Data Acquirer");
}

void Window::dataset_apply()
{
}

void Window::dataset_open()
{
    ;
}

void Window::dataset_refresh_size()
{
    ;
}

void Window::category_add()
{
    ;
}

void Window::category_remove()
{
    ;
}

void Window::category_rename()
{
    ;
}
