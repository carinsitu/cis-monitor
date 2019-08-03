#include "soundplayer.h"

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alut.h"

#include <QDebug>
#include <QFile>

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
        initVoice();
    }
}

void SoundPlayer::initVoice()
{
    alGenSources(static_cast<ALuint>(1), &m_sourceVoice);
    m_error = alGetError();
    if (m_error != AL_NO_ERROR)
        qDebug() << Q_FUNC_INFO << alGetString(m_error);

    m_bufferReady = createAlBufferFromRessource(":/sounds/voices/ready.wav");
    m_bufferGo = createAlBufferFromRessource(":/sounds/voices/go.wav");
    m_bufferYouWin = createAlBufferFromRessource(":/sounds/voices/you_win.wav");
    m_bufferYouLose = createAlBufferFromRessource(":/sounds/voices/you_lose.wav");
    m_bufferRound = createAlBufferFromRessource(":/sounds/voices/round.wav");
    m_bufferHurryUp = createAlBufferFromRessource(":/sounds/voices/hurry_up.wav");
    m_bufferGameOver = createAlBufferFromRessource(":/sounds/voices/game_over.wav");
    m_buffer1 = createAlBufferFromRessource(":/sounds/voices/1.wav");
    m_buffer2 = createAlBufferFromRessource(":/sounds/voices/2.wav");
    m_buffer3 = createAlBufferFromRessource(":/sounds/voices/3.wav");
    m_buffer4 = createAlBufferFromRessource(":/sounds/voices/4.wav");
    m_buffer5 = createAlBufferFromRessource(":/sounds/voices/5.wav");
    m_buffer6 = createAlBufferFromRessource(":/sounds/voices/6.wav");
    m_buffer7 = createAlBufferFromRessource(":/sounds/voices/7.wav");
    m_buffer8 = createAlBufferFromRessource(":/sounds/voices/8.wav");
    m_buffer9 = createAlBufferFromRessource(":/sounds/voices/9.wav");
    m_buffer10 = createAlBufferFromRessource(":/sounds/voices/10.wav");

    sayReady();
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

    m_buffer = createAlBufferFromRessource(":/sounds/engine.wav");
    alSourcei(m_sourceEngine, AL_BUFFER, static_cast<ALint>(m_buffer));
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

void SoundPlayer::say(QString word, ALuint buffer)
{
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

    qDebug() << Q_FUNC_INFO << "Say" << word;
}

void SoundPlayer::sayReady()
{
    say("ready", m_bufferReady);
}

void SoundPlayer::sayGo()
{
    say("go", m_bufferGo);
}

void SoundPlayer::sayYouWin()
{
    say("you win", m_bufferYouWin);
}

void SoundPlayer::sayYouLose()
{
    say("you lose", m_bufferYouLose);
}

void SoundPlayer::sayRound()
{
    say("round", m_bufferRound);
}

void SoundPlayer::sayHurryUp()
{
    say("hurry up", m_bufferHurryUp);
}

void SoundPlayer::sayGameOver()
{
    say("game over", m_bufferGameOver);
}

void SoundPlayer::say1()
{
    say("1", m_buffer1);
}

void SoundPlayer::say2()
{
    say("2", m_buffer2);
}

void SoundPlayer::say3()
{
    say("3", m_buffer3);
}

void SoundPlayer::say4()
{
    say("4", m_buffer4);
}

void SoundPlayer::say5()
{
    say("5", m_buffer5);
}

void SoundPlayer::say6()
{
    say("6", m_buffer6);
}

void SoundPlayer::say7()
{
    say("7", m_buffer7);
}

void SoundPlayer::say8()
{
    say("8", m_buffer8);
}

void SoundPlayer::say9()
{
    say("9", m_buffer9);
}

void SoundPlayer::say10()
{
    say("10", m_buffer10);
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
    // cleanup context
    alDeleteSources(1, &m_sourceEngine);
    alDeleteSources(1, &m_sourceVoice);
    alDeleteBuffers(1, &m_buffer);
    alDeleteBuffers(1, &m_bufferReady);
    alDeleteBuffers(1, &m_bufferGo);
    alDeleteBuffers(1, &m_bufferYouWin);
    alDeleteBuffers(1, &m_bufferYouLose);
    alDeleteBuffers(1, &m_bufferRound);
    alDeleteBuffers(1, &m_bufferHurryUp);
    alDeleteBuffers(1, &m_bufferGameOver);
    alDeleteBuffers(1, &m_buffer1);
    alDeleteBuffers(1, &m_buffer2);
    alDeleteBuffers(1, &m_buffer3);
    alDeleteBuffers(1, &m_buffer4);
    alDeleteBuffers(1, &m_buffer5);
    alDeleteBuffers(1, &m_buffer6);
    alDeleteBuffers(1, &m_buffer7);
    alDeleteBuffers(1, &m_buffer8);
    alDeleteBuffers(1, &m_buffer9);
    alDeleteBuffers(1, &m_buffer10);

    m_device = alcGetContextsDevice(m_context);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}
