#ifndef WINDOWTITLEBAR_H
#define WINDOWTITLEBAR_H

#include <QtGui/QWidget>
#include <QPixmap>

class WindowTitleBar : public QWidget
{
Q_OBJECT

public:
  WindowTitleBar(QWidget *parent = 0);
  ~WindowTitleBar();
private:
  QPixmap *m_Cache;
protected:
  void resizeEvent(QResizeEvent *event);
  void paintEvent (QPaintEvent  *event);
};

#endif
