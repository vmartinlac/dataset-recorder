#pragma once

#include <QWidget>
#include <memory>
#include "Dataset.h"
#include "MicrophoneManager.h"

class QComboBox;
class QStackedLayout;
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

    QStackedLayout* m_sensor_stacked_layout;
    QWidget* m_sensor_image;
    QWidget* m_sensor_sound;
    QComboBox* m_sensor_microphone;

    std::unique_ptr<Dataset> m_dataset;
    std::unique_ptr<MicrophoneManager> m_microphone;

protected:

    QGroupBox* create_dataset_groupbox();
    QGroupBox* create_category_groupbox();
    QGroupBox* create_sample_groupbox();
    QGroupBox* create_sensor_groupbox();
    QWidget* create_image_widget();
    QWidget* create_sound_widget();

    int get_current_category();

signals:

    void dataset_path_changed();
    void dataset_kind_changed();

    void category_changed();

protected slots:

    void dataset_open();
    void dataset_update_total_size();

    void category_add();
    void category_rename();
    void category_remove();
    void category_update_list();

    void sample_update_next_filename();
    void sample_update_category();

    void sensor_switch();
    void sensor_toggle_record_sound(bool);
    void sensor_select_microphone();
};

