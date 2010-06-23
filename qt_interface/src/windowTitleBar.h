#ifndef WINDOWTITLEBAR_H
#define WINDOWTITLEBAR_H

#include <QtGui/QWidget>
#include <QPixmap>

class windowTitleBar : public QWidget
{
Q_OBJECT

public:
  windowTitleBar(QWidget *parent = 0);
  ~windowTitleBar();
private:
  QPixmap *m_Cache;
protected:
  void resizeEvent(QResizeEvent *event);
  void paintEvent (QPaintEvent  *event);
};

#endif
