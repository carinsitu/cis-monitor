#include "soundplayer.h"

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alut.h"

#include <QDebug>
#include <QFile>
#include <QDir>

SoundPlayer::SoundPlayer(QObject* parent) : QObject(parent), m_defaultEnginePitch(1)
{
}

void SoundPlayer::init(char* deviceName)
{
    cleanContext();

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
        initVoices();
    }
}

void SoundPlayer::initVoices()
{
    alGenSources(static_cast<ALuint>(1), &m_sourceVoice);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    loadVoices();

    say("ready");
}

void SoundPlayer::loadVoices()
{
    QDir voicesDirectory(":/sounds/voices");
    for (QFileInfo voiceFileInfo : voicesDirectory.entryInfoList()) {
        QString text = voiceFileInfo.baseName().replace('_', ' ');
        m_voicesHash[text] = createAlBufferFromRessource(voiceFileInfo.filePath());
    }
}

void SoundPlayer::initEngine()
{
    alGenSources(static_cast<ALuint>(1), &m_sourceEngine);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    alSourcef(m_sourceEngine, AL_PITCH, static_cast<ALfloat>(m_defaultEnginePitch));
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    alSourcef(m_sourceEngine, AL_GAIN, 1);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    alSource3f(m_sourceEngine, AL_POSITION, 0, 0, 0);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    alSource3f(m_sourceEngine, AL_VELOCITY, 0, 0, 0);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    alSourcei(m_sourceEngine, AL_LOOPING, AL_TRUE);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    m_bufferEngine = createAlBufferFromRessource(":/sounds/engine.wav");
    alSourcei(m_sourceEngine, AL_BUFFER, static_cast<ALint>(m_bufferEngine));
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);
}

ALuint SoundPlayer::createAlBufferFromRessource(const QString& ressource)
{
    ALuint buffer;
    // ALUT init
    if (!alutInitWithoutContext(nullptr, nullptr))
        qDebug() << Q_FUNC_INFO << "Failed alutInitWithoutContext(NULL, NULL)";

    ALCenum alutError = alutGetError();
    if (alutError != ALUT_ERROR_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alutGetErrorString(alutError);

    // make sure to call alutInitWithoutContext first
    QFile soundFile(ressource);
    soundFile.open(QIODevice::ReadOnly);
    buffer = alutCreateBufferFromFileImage(soundFile.readAll(), static_cast<ALsizei>(soundFile.size()));
    alutError = alutGetError();
    if (alutError != ALUT_ERROR_NO_ERROR)
        qDebug() << Q_FUNC_INFO << "Failed alutCreateBufferFromFileImage(fic.readAll(), fic.size())";

    alutExit();
    return buffer;
}

void SoundPlayer::say(const QString& text)
{
    if (!m_voicesHash.contains(text)) {
        qDebug() << Q_FUNC_INFO << "Voice not found: " << text;
        return;
    }

    ALuint buffer = m_voicesHash.value(text);

    ALint bufferCount;
    alGetSourcei(m_sourceVoice, AL_BUFFERS_PROCESSED, &bufferCount);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << "Failed alSourcei(m_sourceVoice, AL_BUFFERS_PROCESSED, bufferCount)";

    ALCenum sourceState;
    alGetSourcei(m_sourceVoice, AL_SOURCE_STATE, &sourceState);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << "Failed alGetSourcei(m_sourceVoice, AL_SOURCE_STATE, &sourceState)";

    ALuint buffers;
    alSourceUnqueueBuffers(m_sourceVoice, bufferCount, &buffers);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    alSourceQueueBuffers(m_sourceVoice, static_cast<ALsizei>(1), &buffer);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    if (sourceState != AL_PLAYING)
        alSourcePlay(m_sourceVoice);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    qDebug() << Q_FUNC_INFO << "Say" << text;
}

void SoundPlayer::startEngine()
{
    alSourcePlay(m_sourceEngine);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);
    qDebug() << Q_FUNC_INFO << "Engine started";
}

void SoundPlayer::stopEngine()
{
    alSourceStop(m_sourceEngine);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);
    qDebug() << Q_FUNC_INFO << "Engine stopped";
}

void SoundPlayer::setEngineSpeed(qint16 speed)
{
    qreal pitchSpeed = m_defaultEnginePitch + (speed * 0.01);
    alSourcef(m_sourceEngine, AL_PITCH, static_cast<ALfloat>(pitchSpeed));
    // check for errors
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);
}

QStringList SoundPlayer::listAllDevices()
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

void SoundPlayer::onSoundCardSelected(QString deviceName)
{
    if (deviceName != "") {
        init(deviceName.toUtf8().data());
        startEngine();
    } else {
        stopEngine();
    }
}

void SoundPlayer::cleanContext()
{
    alDeleteSources(1, &m_sourceEngine);
    alDeleteSources(1, &m_sourceVoice);
    alDeleteBuffers(1, &m_bufferEngine);

    for (ALuint voiceBuffer : m_voicesHash) {
        alDeleteBuffers(1, &voiceBuffer);
    }

    m_device = alcGetContextsDevice(m_context);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}
