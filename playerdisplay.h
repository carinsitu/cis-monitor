#ifndef PLAYERDISPLAY_H
#define PLAYERDISPLAY_H

#include <QObject>

#include <QGraphicsScene>
#include <QCameraInfo>

class PlayerDisplay : public QObject
{
    Q_OBJECT
public:
    explicit PlayerDisplay(const QCameraInfo& cameraInfo, QObject* parent = nullptr);
    QGraphicsItemGroup* osd() { return m_osd; }
    void setMessage(QString message);

private:
    QGraphicsScene* m_scene;
    QGraphicsItemGroup* m_osd;
    QGraphicsSimpleTextItem* m_text;

signals:

public slots:
};

#endif // PLAYERDISPLAY_H
