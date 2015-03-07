#ifndef FRAME_H
#define FRAME_H
#include <QtGui>

#include "titlebar.h"

class Frame:public QFrame
{
public:
    Frame();

    QWidget* contentWidget() const { return m_content;}
    TitleBar* titleBar() const { return m_titleBar;}

    void mouseMoveEvent(QMouseEvent* );
    void mousePressEvent(QMouseEvent* );
    void mouseReleaseEvent(QMouseEvent* );

private:
    TitleBar* m_titleBar;
    QWidget *m_content;
    QPoint m_old_pos;
    bool m_mouse_down;
    bool left,right,bottom;
};

#endif // FRAME_H
