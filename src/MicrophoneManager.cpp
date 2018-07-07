#include <portaudio.h>
#include <sndfile.hh>
#include <iostream>
#include "MicrophoneManager.h"

int MicrophoneManager::callback(
    const void* input,
    void* output,
    unsigned long frame_count,
    const PaStreamCallbackTimeInfo* time_info,
    PaStreamCallbackFlags status_flags,
    void* user_data)
{
    CallbackData* data = static_cast<CallbackData*>(user_data);
}

MicrophoneManager* MicrophoneManager::m_instance = nullptr;

MicrophoneManager::MicrophoneManager() :
    m_stream(nullptr),
    m_callback_data({nullptr})
{
    if(m_instance != nullptr) abort();
    m_instance = this;

    Pa_Initialize();

    PaDeviceIndex count = Pa_GetDeviceCount();

    for(PaDeviceIndex i=0; i<count; i++)
    {
        const PaDeviceInfo* info = Pa_GetDeviceInfo(i);

        if( info->maxInputChannels > 0 )
        {
            Device dev;
            dev.name = info->name;
            dev.index = i;
            m_devices.push_back(dev);
        }
    }
}

MicrophoneManager::~MicrophoneManager()
{
    Pa_Terminate();

    if( m_callback_data.file != nullptr)
    {
        std::cerr << "Warning ! Some output sound file was not closed !" << std::endl;
        sf_close(m_callback_data.file);
        m_callback_data.file = nullptr;
    }

    if(m_instance != this) abort();
    m_instance = nullptr;
}

bool MicrophoneManager::stopRecording()
{
    const PaError ret1 = Pa_StopStream(m_stream);

    const int ret2 = sf_close(m_callback_data.file);
    m_callback_data.file = nullptr;

    return ( ret1 == paNoError && ret2 == 0 );
}

int MicrophoneManager::getNumMicrophones()
{
    return int( m_devices.size() );
}

QString MicrophoneManager::getMicrophoneName(int id)
{
    return m_devices[id].name;
}

bool MicrophoneManager::openMicrophone(int id)
{
    closeMicrophone();

    const PaDeviceInfo* info = Pa_GetDeviceInfo(m_devices[id].index);

    if(info == nullptr)
        return false;

    PaStreamParameters parameters;

    // TMP TODO
    std::cout << info->defaultHighInputLatency << std::endl;
    std::cout << info->defaultLowInputLatency << std::endl;
    //

    parameters.device = m_devices[id].index;
    parameters.channelCount = 1;
    parameters.suggestedLatency = info->defaultHighInputLatency;
    parameters.hostApiSpecificStreamInfo = nullptr;
    parameters.sampleFormat = paFloat32;

    const PaError ret = Pa_OpenStream(
        &m_stream, 
        &parameters,
        nullptr,
        info->defaultSampleRate,
        paFramesPerBufferUnspecified,
        paNoFlag,
        callback,
        &m_callback_data);

    if( ret != paNoError )
    {
        m_stream = nullptr;
        return false;
    }
    else
    {
        return true;
    }
}

bool MicrophoneManager::startRecording(const QString& destination_file)
{
    // TODO : complete adequate fields in 
    const PaError ret = Pa_StartStream(m_stream);
    return (ret == paNoError);
}

void MicrophoneManager::closeMicrophone()
{
    if( m_stream != nullptr )
    {
        Pa_CloseStream(m_stream);
        m_stream = nullptr;
    }
}

