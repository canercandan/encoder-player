#include "windowTitleBar.h"
#include <QPixmap>
#include <QPainter>

windowTitleBar::windowTitleBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(33);
}

windowTitleBar::~windowTitleBar()
{

}

void windowTitleBar::resizeEvent(QResizeEvent *event)
{
  Q_UNUSED(event);

  delete m_Cache; // Remove old cache

  m_Cache = new QPixmap(size());  // Create a cache with same size as the widget

  m_Cache->fill(Qt::transparent);  // Create a the transparent background

  QPainter painter(m_Cache); // Start painting the cache

  QColor lightBlue    (177, 177, 203, 255);
  QColor gradientStart(  0,   0,   0,   0);
  QColor gradientEnd  (  0,   0,   0, 220);

  QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
  linearGrad.setColorAt(0, gradientStart);
  linearGrad.setColorAt(1, gradientEnd);

  /********** Title bar's frame **********/
  QPolygon frame;

  frame << QPoint(         20,  4)
        << QPoint(width() - 4,  4)
        << QPoint(width() - 4, 32)
        << QPoint(          4, 32)
        << QPoint(          4, 20);

  painter.setPen  (QPen  (lightBlue ));
  painter.setBrush(QBrush(linearGrad));

  painter.drawPolygon(frame);
  /***************************************/

  /********** Title bar's buttons area **********/
  QPolygon buttons;

  buttons << QPoint(width() - 80,  4)
          << QPoint(width() -  4,  4)
          << QPoint(width() -  4, 32)
          << QPoint(width() - 88, 32)
          << QPoint(width() - 88, 12);

  painter.setPen  (QPen  (lightBlue));
  painter.setBrush(QBrush(lightBlue));

  painter.drawPolygon(buttons);
  /**********************************************/
}

void windowTitleBar::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event);

  if(m_Cache != NULL)
  {
    QPainter painter(this);

    painter.drawPixmap(0, 0, *m_Cache);
  }
}
