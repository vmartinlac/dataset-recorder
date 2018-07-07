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
    const float* array = static_cast<const float*>(input);

    unsigned long i=0;
    while( i < frame_count && data->start < data->buffer.size() )
    {
        data->buffer[data->start] = array[i];
        i++;
        data->start++;
    }

    return paContinue;
}

MicrophoneManager* MicrophoneManager::m_instance = nullptr;

MicrophoneManager::MicrophoneManager() :
    m_stream(nullptr)
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
    closeMicrophone();

    Pa_Terminate();

    if(m_instance != this) abort();
    m_instance = nullptr;
}

bool MicrophoneManager::stopRecording()
{
    if( m_stream != nullptr && Pa_IsStreamActive(m_stream) )
    {
        const PaError ret1 = Pa_StopStream(m_stream);

        if( ret1 != paNoError )
        {
            return false;
        }
        else
        {
            SF_INFO info;

            info.frames = m_callback_data.buffer.size();
            info.samplerate = int(Pa_GetStreamInfo(m_stream)->sampleRate);
            info.channels = 1;
            info.format = SF_FORMAT_WAV|SF_FORMAT_FLOAT;
            info.sections = 0;
            info.seekable = 0;

            SNDFILE* file = sf_open( m_output_filename.toLocal8Bit().data(), SFM_WRITE, &info );

            if(file == nullptr)
            {
                std::cerr << sf_strerror(nullptr) << std::endl;
                return false;
            }
            else
            {
                sf_write_float( file, &m_callback_data.buffer.front(), m_callback_data.start );
                const int ret = sf_close(file);

                if(ret == 0)
                {
                    return true;
                }
                else
                {
                    std::cerr << sf_error_number(ret) << std::endl;
                    return false;
                }
            }
        }
    }
    else
    {
        return true;
    }
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

    if( id < 0 || id >= m_devices.size() )
        return false;

    const PaDeviceInfo* info = Pa_GetDeviceInfo(m_devices[id].index);

    if(info == nullptr)
        return false;

    PaStreamParameters parameters;

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
    bool is_ok = true;

    if(is_ok)
    {
        is_ok = m_stream != nullptr;
    }

    if(is_ok)
    {
        if( Pa_IsStreamActive(m_stream) )
        {
            is_ok = stopRecording();
        }
    }

    if( is_ok )
    {
        m_output_filename = destination_file;
        m_callback_data.buffer.resize(60*44100);
        m_callback_data.start = 0;

        is_ok = ( Pa_StartStream(m_stream) == paNoError );
    }

    return is_ok;
}

void MicrophoneManager::closeMicrophone()
{
    if( m_stream != nullptr )
    {
        stopRecording();

        Pa_CloseStream(m_stream);
        m_stream = nullptr;
    }
}

