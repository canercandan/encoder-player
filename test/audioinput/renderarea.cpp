#include <QPainter>

#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    level = 0;
    setMinimumHeight(30);
    setMinimumWidth(200);
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.drawRect(QRect(painter.viewport().left()+10,
                           painter.viewport().top()+10,
                           painter.viewport().right()-20,
                           painter.viewport().bottom()-20));
    if (level == 0)
        return;

    painter.setPen(Qt::red);

    int pos = ((painter.viewport().right()-20)-(painter.viewport().left()+11))*level/100;
    for (int i = 0; i < 10; ++i) {
        int x1 = painter.viewport().left()+11;
        int y1 = painter.viewport().top()+10+i;
        int x2 = painter.viewport().left()+20+pos;
        int y2 = painter.viewport().top()+10+i;
        if (x2 < painter.viewport().left()+10)
            x2 = painter.viewport().left()+10;

        painter.drawLine(QPoint(x1, y1),QPoint(x2, y2));
    }
}

void RenderArea::setLevel(int value)
{
    level = value;
    repaint();
}
