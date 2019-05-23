#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QDialog>
#include <QGraphicsView>

class PlayerView : public QDialog
{
    Q_OBJECT
public:
    explicit PlayerView(QWidget *parent = nullptr);
    QGraphicsView* view() { return m_view; }
signals:

private:
     QGraphicsView* m_view;

private slots:
    void mousePressEvent(QMouseEvent *event);
    void tbFullScreenToggled(bool on);
    void keyPressEvent(QKeyEvent *e);
    void resizeEvent(QResizeEvent *event);

public slots:
};

#endif // PLAYERVIEW_H
