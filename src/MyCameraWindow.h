#ifndef MYCAMERAWINDOW_H_
#define MYCAMERAWINDOW_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <QWidget>
#include <QVBoxLayout>

#include "qopencv/QOpenCVWidget.h"

class MyCameraWindow : public QWidget
{
    Q_OBJECT

public:
    MyCameraWindow(CvCapture* cam, QWidget* parent = 0);

    void start();
    void stop();

    std::vector< IplImage* > getImages(){return _images;}

protected:
    void timerEvent(QTimerEvent*);

private:
    bool _writable;
    std::vector< IplImage* > _images;
    QOpenCVWidget* _cvwidget;
    CvCapture* _camera;
};


#endif /*MYCAMERAWINDOW_H_*/
