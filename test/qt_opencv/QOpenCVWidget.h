#ifndef QOPENCVWIDGET_H
#define QOPENCVWIDGET_H

#include <opencv/cv.h>

#include <QWidget>
#include <QImage>

class QLabel;
class QVBoxLayout;

class QOpenCVWidget : public QWidget
{
public:
    QOpenCVWidget(QWidget* parent = 0);
    ~QOpenCVWidget(void);

    void putImage(IplImage*);

private:
    QLabel* imagelabel;
    QVBoxLayout* layout;

    QImage image;
};

#endif
