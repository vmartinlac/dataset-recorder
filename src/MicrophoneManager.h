#pragma once

#include <QString>
#include <vector>
#include <portaudio.h>

class MicrophoneManager
{
public:

    MicrophoneManager();
    ~MicrophoneManager();
    int getNumMicrophones();
    QString getMicrophoneName(int id);
    bool openMicrophone(int id);
    void closeMicrophone();
    bool startRecording(const QString& destination_file);
    bool stopRecording();

    static MicrophoneManager* instance() { return m_instance; }

protected:

    struct Device
    {
        QString name;
        PaDeviceIndex index;
    };

    struct CallbackData
    {
        size_t start;
        std::vector<float> buffer;
    };

protected:

    static MicrophoneManager* m_instance;
    PaStream* m_stream;
    std::vector<Device> m_devices;
    CallbackData m_callback_data;

protected:

    static int callback(
        const void* input,
        void* output,
        unsigned long frame_count,
        const PaStreamCallbackTimeInfo* time_info,
        PaStreamCallbackFlags status_flags,
        void* user_data);
};
