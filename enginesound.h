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
    void start();
    void stop();
    void setSpeed(qint16 speed);
    QStringList listAllDevices();

private:
    ALCenum m_error;
    ALuint m_source;
    qreal m_defaultPitch;
    ALCdevice* m_device;
    ALCcontext* m_context;
    ALuint m_buffer;
signals:

public slots:
};

#endif // ENGINESOUND_H
