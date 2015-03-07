#include "titlebar.h"

TitleBar::TitleBar(QFrame *parent)
{
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Window);
   // setStyleSheet("*{"
   //              "background-image:url(:/images/background.png);"

   //               "}");

    minimize = new QToolButton(this);
    maximize = new QToolButton(this);
    close = new QToolButton(this);

    QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    close->setIcon(pix);
   // close->setStyleSheet("QToolButton{border-image:url(:/images/toolbutton.png);}");

    maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
    maximize->setIcon(maxPix);
   // maximize->setStyleSheet("QToolButton{border-image:url(:/images/toolbutton.png);}");

    pix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    minimize->setIcon(pix);
   // minimize->setStyleSheet("QToolButton{border-image:url(:/images/toolbutton.png);}");

    restorePix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);

    minimize->setMinimumSize(30,30);
    maximize->setMinimumSize(30,30);
    close->setMinimumSize(30,30);

    QLabel* label = new QLabel(this);
    label->setText(tr(" 指挥控制仿真平台 "));
    label->setStyleSheet("QLabel{font:14pt; color:white; font-family:\"AR PL UKai TW MBE\";}");
    parent->setWindowTitle(tr("Window Title"));

    QHBoxLayout* hlayout = new QHBoxLayout(this);

    hlayout->addWidget(label);
    hlayout->addWidget(minimize);
    hlayout->addWidget(maximize);
    hlayout->addWidget(close);

    hlayout->insertStretch(1,500);
    hlayout->setSpacing(0);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    maxNormal = false;

    connect(close,SIGNAL(clicked()),parent,SLOT(close()));
    connect(minimize,SIGNAL(clicked()),this,SLOT(showSmall()));
    connect(maximize,SIGNAL(clicked()),this,SLOT(showMaxRestore()));

}

void TitleBar::showSmall()
{
    parentWidget()->showMinimized();
}

void TitleBar::showMaxRestore()
{
    if(maxNormal)
    {
        parentWidget()->showNormal();
        maxNormal= !maxNormal;
        maximize->setIcon(restorePix);
    }else{
        parentWidget()->showMaximized();
        maxNormal = !maxNormal;
        maximize->setIcon(restorePix);
    }
}

void TitleBar::mousePressEvent(QMouseEvent *me)
{
    startPos = me->globalPos();
    clickPos = mapToParent(me->pos());
}

void TitleBar::mouseMoveEvent(QMouseEvent *me)
{
    if(maxNormal)
    {
        return;
    }
    parentWidget()->move(me->globalPos()-clickPos);
}

