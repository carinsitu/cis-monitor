#include "playerview.h"

#include <QLayout>
#include <QMouseEvent>

#include <QPushButton>

PlayerView::PlayerView(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *lMain = new QVBoxLayout(this);
    lMain->setSpacing(0);
    lMain->setMargin(0);
    lMain->setContentsMargins(0,0,0,0);

    m_view = new QGraphicsView(this);
    m_view->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    // m_view->setFixedSize(740,580);
    this->setStyleSheet("background-color:black;");
    this->layout()->addWidget(m_view);
    this->layout()->addWidget(new QPushButton());

    // m_view->show();

    // this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
}

void PlayerView::resizeEvent(QResizeEvent *event)
{
    m_view->fitInView(0,0,640,480);
}

void PlayerView::mousePressEvent(QMouseEvent *event)
{
    if (event->type() ==  QEvent::MouseButtonDblClick)
    {
        tbFullScreenToggled(false);
    }
}

void PlayerView::tbFullScreenToggled(bool on)
{
    (void)on;
    if(isFullScreen()) {
         this->setWindowState(Qt::WindowMaximized);
      } else {
         this->setWindowState(Qt::WindowFullScreen);
      }
}

void PlayerView::keyPressEvent(QKeyEvent *e) {
    if(e->key() != Qt::Key_Escape)
        QDialog::keyPressEvent(e);
    else {
        tbFullScreenToggled(false);
    }
}
