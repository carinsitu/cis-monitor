#include "enginesound.h"
#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alut.h"
#include <QDebug>
#include <QFile>

EngineSound::EngineSound(QObject* parent) : QObject(parent), m_defaultPitch(1)
{
}

void EngineSound::init(char* deviceName)
{
    // cleanup context
    alDeleteSources(1, &m_source);
    alDeleteBuffers(1, &m_buffer);
    m_device = alcGetContextsDevice(m_context);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);

    // Open device (NULL is for default sound device)
    if (deviceName)
        qDebug() << Q_FUNC_INFO << "Connect device: " << deviceName;
    else
        qDebug() << Q_FUNC_INFO << "Connect device: "
                 << "System default";

    m_device = alcOpenDevice(deviceName);
    if (!m_device)
        qDebug() << Q_FUNC_INFO << "Failed alcOpenDevice: " << deviceName;

    if (m_device) {
        m_context = alcCreateContext(m_device, nullptr);
        alcMakeContextCurrent(m_context);

        // Activation du contexte
        if (!alcMakeContextCurrent(m_context))
            qDebug() << Q_FUNC_INFO << "Failed alcMakeContextCurrent(Context)";

        // Listener
        ALfloat listenerOri[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};

        alListener3f(AL_POSITION, 0, 0, 1.0f);
        m_error = alGetError();
        if (m_error != AL_NO_ERROR)
            qDebug() << Q_FUNC_INFO << alGetString(m_error);

        alListener3f(AL_VELOCITY, 0, 0, 0);
        m_error = alGetError();
        if (m_error != AL_NO_ERROR)
            qDebug() << Q_FUNC_INFO << alGetString(m_error);

        alListenerfv(AL_ORIENTATION, listenerOri);
        m_error = alGetError();
        if (m_error != AL_NO_ERROR)
            qDebug() << Q_FUNC_INFO << alGetString(m_error);

        initEngine();
    }
}

        alSourcef(m_source, AL_PITCH, static_cast<ALfloat>(m_defaultPitch));
        m_error = alGetError();
        if (m_error != AL_NO_ERROR)
            qDebug() << Q_FUNC_INFO << alGetString(m_error);

        alSourcef(m_source, AL_GAIN, 1);
        m_error = alGetError();
        if (m_error != AL_NO_ERROR)
            qDebug() << Q_FUNC_INFO << alGetString(m_error);

void EngineSound::initEngine()
{
    alGenSources(static_cast<ALuint>(1), &m_source);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    alSourcef(m_source, AL_PITCH, static_cast<ALfloat>(m_defaultPitch));
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    alSourcef(m_source, AL_GAIN, 1);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    alSource3f(m_source, AL_POSITION, 0, 0, 0);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    alSource3f(m_source, AL_VELOCITY, 0, 0, 0);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    alSourcei(m_source, AL_LOOPING, AL_TRUE);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    m_buffer = sampleBuffer(":/wav/engine.wav");
    alSourcei(m_source, AL_BUFFER, static_cast<ALint>(m_buffer));
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);
}

ALuint EngineSound::sampleBuffer(QString ressource)
{
    ALuint buffer;
    // ALUT init
    if (!alutInitWithoutContext(nullptr, nullptr))
        qDebug() << Q_FUNC_INFO << "Failed alutInitWithoutContext(NULL, NULL)";

    ALCenum alutError = alutGetError();
    if (alutError != ALUT_ERROR_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alutGetErrorString(alutError);

    // make sure to call alutInitWithoutContext first
    QFile fic(ressource);
    fic.open(QIODevice::ReadOnly);
    buffer = alutCreateBufferFromFileImage(fic.readAll(), static_cast<ALsizei>(fic.size()));
    alutError = alutGetError();
    if (alutError != ALUT_ERROR_NO_ERROR)
        qDebug() << Q_FUNC_INFO << "Failed alutCreateBufferFromFileImage(fic.readAll(), fic.size())";

    alutExit();
    return buffer;
}

void EngineSound::start()
{
    alSourcePlay(m_source);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);
    qDebug() << Q_FUNC_INFO << "Engine started";
}

void EngineSound::stop()
{
    alSourceStop(m_source);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);
    qDebug() << Q_FUNC_INFO << "Engine stopped";
}

void EngineSound::setSpeed(qint16 speed)
{
    qreal pitchSpeed = m_defaultPitch + (speed * 0.01);
    alSourcef(m_source, AL_PITCH, static_cast<ALfloat>(pitchSpeed));
    // check for errors
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);
}

QStringList EngineSound::listAllDevices()
{
    // Check if we can enumerate devices
    QStringList devicesList;

    // Check if we can enumerate ALL devices
    ALboolean enumerateAll;
    enumerateAll = alcIsExtensionPresent(nullptr, "ALC_ENUMERATE_ALL_EXT");
    if (enumerateAll == AL_FALSE)
        qDebug() << Q_FUNC_INFO << "Failed alcIsExtensionPresent(nullptr, ALC_ENUMERATE_ALL_EXT)";

    const ALCchar* DeviceList = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);

    const ALCchar *device = DeviceList, *next = DeviceList + 1;
    size_t len = 0;

    while (device && *device != '\0' && next && *next != '\0') {
        devicesList.append(device);
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }
    return devicesList;
}

void EngineSound::onSoundCardSelected(QString deviceName)
{
    if (deviceName != "") {
        init(deviceName.toUtf8().data());
        start();
    } else {
        stop();
    }
}
