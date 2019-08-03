#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QObject>

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alut.h"

#include <QHash>

class SoundPlayer : public QObject
{
    Q_OBJECT
public:
    explicit SoundPlayer(QObject* parent = nullptr);
    void init(char* deviceName = nullptr);
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
    ALuint m_bufferEngine;
    QHash<QString, ALuint> m_voicesHash;

    void initEngine();
    void initVoices();
    void loadVoices();
    void say(const QString& text);
    ALuint createAlBufferFromRessource(const QString& ressource);
    void cleanContext();
signals:

public slots:
    void onSoundCardSelected(QString deviceName);
};

#endif // SOUNDPLAYER_H
