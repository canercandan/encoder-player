#ifndef MYMOVIEWINDOW_H_
#define MYMOVIEWINDOW_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <QWidget>
#include <QVBoxLayout>

#include "qopencv/QOpenCVWidget.h"

class MyMovieWindow : public QWidget
{
    Q_OBJECT

public:
    MyMovieWindow(QWidget* parent = 0);

    void setImages(std::vector< IplImage* >&);

    void start();
    void stop();

protected:
    void timerEvent(QTimerEvent*);

private:
    std::vector< IplImage* > _images;
    unsigned int _position;
    int _timerId;
    QOpenCVWidget* _cvwidget;
};


#endif /*MYMOVIEWINDOW_H_*/
