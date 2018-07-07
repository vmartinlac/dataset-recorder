#include <QMessageBox>
#include <QInputDialog>
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
#include <iostream>
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
    grp_dataset->setLayout(form_dataset);
    grp_dataset->setTitle("Dataset");

    m_dataset_size = dataset_size;
    m_dataset_kind = dataset_kind_group;
    m_dataset_path = dataset_path;

    connect(dataset_open_btn, &QPushButton::clicked, this, &Window::dataset_open);
    connect(m_dataset_path, &QLineEdit::textChanged, this, &Window::dataset_path_changed);
    connect(m_dataset_kind, SIGNAL(buttonClicked(int)), this, SIGNAL(dataset_kind_changed()));
    connect( this, &Window::dataset_path_changed, this, &Window::dataset_update_total_size );

    return grp_dataset;
}

void Window::category_update_list()
{
    m_category_list->clear();

    if(m_dataset->isValid())
    {
        for(int i=0; i<m_dataset->getNumCategories(); i++)
        {
            QListWidgetItem* item = new QListWidgetItem();
            item->setText( m_dataset->getCategoryName(i) + " (" + QString::number(m_dataset->getNumSamplesInCategory(i)) + " samples)" );
            item->setData( Qt::UserRole, i);
            m_category_list->addItem( item );
        }
    }
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
    connect( category_list, &QListWidget::currentItemChanged, this, &Window::category_changed );
    connect( this, &Window::dataset_path_changed, this, &Window::category_update_list );

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

    m_sample_prefix = sample_prefix;
    m_sample_next_filename = sample_next_filename;
    m_sample_category = sample_category;

    connect( sample_prefix, &QLineEdit::textChanged, this, &Window::sample_update_next_filename );
    connect( this, &Window::dataset_path_changed, this, &Window::sample_update_next_filename );
    connect( this, &Window::dataset_kind_changed, this, &Window::sample_update_next_filename );
    connect( this, &Window::category_changed, this, &Window::sample_update_next_filename );
    connect( this, &Window::category_changed, this, &Window::sample_update_category );

    return sample_groupbox;
}

QGroupBox* Window::create_sensor_groupbox()
{
    QGroupBox* sensor_groupbox = new QGroupBox();
    QStackedLayout* sensor_stackedlayout = new QStackedLayout();

    sensor_groupbox->setTitle("Sensor");
    sensor_groupbox->setLayout(sensor_stackedlayout);

    sensor_stackedlayout->addWidget( create_image_widget() );
    sensor_stackedlayout->addWidget( create_sound_widget() );

    return sensor_groupbox;
}

Window::Window(QWidget* parent) : QWidget(parent)
{
    m_dataset.reset( new Dataset() );

    QGridLayout* l = new QGridLayout();
    l->addWidget(create_dataset_groupbox(), 0, 0);
    l->addWidget(create_category_groupbox(), 1, 0);
    l->addWidget(create_sample_groupbox(), 2, 0);
    l->addWidget(create_sensor_groupbox(), 0, 1, 3, 1);

    setLayout(l);
    setWindowTitle("Data Acquirer");
}

void Window::dataset_open()
{
    QString ret = QFileDialog::getExistingDirectory(this, "Open dataset");

    m_dataset_path->setText(ret);
    m_dataset->set(ret);

    dataset_path_changed();
}

void Window::sample_update_next_filename()
{
    int cat = get_current_category();

    if( cat >= 0 )
    {
        QString prefix = m_sample_prefix->text();
        QString ext = (m_dataset_kind->checkedId() == ID_IMAGE) ? "png" : "wav";

        m_sample_next_filename->setText( m_dataset->getNextSampleFilename(cat, prefix, ext ) );
    }
    else
    {
        m_sample_next_filename->setText("");
    }
}

void Window::dataset_update_total_size()
{
    if(m_dataset->isValid())
    {
        m_dataset_size->setText(QString::number(m_dataset->getTotalNumSamples()));
    }
    else
    {
        m_dataset_size->setText("N/A");
    }
}

void Window::category_add()
{
    QString txt = QInputDialog::getText(this, "Name", "Name of the new category ?");

    if(txt.isEmpty() == false)
    {
        const bool ret = m_dataset->addCategory(txt);
        if( ret == false )
        {
            QMessageBox::critical(this, "Error", "Failed !");
        }
        dataset_path_changed();
    }
}

void Window::category_remove()
{
    const int cat = get_current_category();

    if( cat >= 0 )
    {
        const int confirmation = QMessageBox::question(
            this,
            "Confirmation",
            "Are you sure you want to delete selected category and all its content ?",
            QMessageBox::Yes|QMessageBox::No);

        if( confirmation == QMessageBox::Yes )
        {
            const bool ret = m_dataset->removeCategory(cat);
            if( ret == false )
            {
                QMessageBox::critical(this, "Error", "Failed !");
            }
            dataset_path_changed();
        }
    }
}

void Window::category_rename()
{
    const int cat = get_current_category();

    if( cat >= 0 )
    {
        QString txt = QInputDialog::getText(this, "New name", "New name of this category ?");

        if(txt.isEmpty() == false)
        {
            const bool ret = m_dataset->renameCategory(cat, txt);
            if( ret == false )
            {
                QMessageBox::critical(this, "Error", "Failed !");
            }
            dataset_path_changed();
        }
    }
}

int Window::get_current_category()
{
    QListWidgetItem* item = m_category_list->currentItem();

    if( m_dataset->isValid() && m_dataset->getNumCategories() > 0 && item != nullptr )
    {
        return m_category_list->currentItem()->data(Qt::UserRole).toInt();
    }
    else
    {
        return -1;
    }
}

QWidget* Window::create_image_widget()
{
    return new QWidget();
}

QWidget* Window::create_sound_widget()
{
    return new QWidget();
}

void Window::sample_update_category()
{
    const int cat = get_current_category();

    if(cat >= 0)
    {
        m_sample_category->setText( m_dataset->getCategoryName(cat) );
    }
    else
    {
        m_sample_category->setText("N/A");
    }
}
