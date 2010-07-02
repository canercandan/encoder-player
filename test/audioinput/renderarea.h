#ifndef _RenderArea_h
#define _RenderArea_h

#include <QPixmap>
#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent = 0);

    void setLevel(int value);

protected:
    void paintEvent(QPaintEvent *event);

private:
    int level;
    QPixmap pixmap;
};

#endif // !_RenderArea_h
