#ifndef ENGINESOUND_H
#define ENGINESOUND_H

#include <QObject>

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alut.h"

class EngineSound : public QObject
{
    Q_OBJECT
public:
    explicit EngineSound(QObject* parent = nullptr);
    void init(char* deviceName = nullptr);
    void sayReady();
    void sayGo();
    void sayYouWin();
    void sayYouLose();
    void sayRound();
    void sayHurryUp();
    void sayGameOver();
    void say1();
    void say2();
    void say3();
    void say4();
    void say5();
    void say6();
    void say7();
    void say8();
    void say9();
    void say10();
    void startEngine();
    void stopEngine();
    void setEngineSpeed(qint16 speed);
    QStringList listAllDevices();

private:
    ALCenum m_error;
    ALuint m_sourceEngine;
    ALuint m_sourceVoice;
    qreal m_defaultEnginePitch;
    ALCdevice* m_device;
    ALCcontext* m_context;
    ALuint m_buffer;
    ALuint m_bufferReady;
    ALuint m_bufferGo;
    ALuint m_bufferYouWin;
    ALuint m_bufferYouLose;
    ALuint m_bufferRound;
    ALuint m_bufferHurryUp;
    ALuint m_bufferGameOver;
    ALuint m_buffer1;
    ALuint m_buffer2;
    ALuint m_buffer3;
    ALuint m_buffer4;
    ALuint m_buffer5;
    ALuint m_buffer6;
    ALuint m_buffer7;
    ALuint m_buffer8;
    ALuint m_buffer9;
    ALuint m_buffer10;
    void initEngine();
    void initVoice();
    void say(QString word, ALuint buffer);
    ALuint sampleBuffer(QString ressource);
signals:

public slots:
    void onSoundCardSelected(QString deviceName);
};

#endif // ENGINESOUND_H
