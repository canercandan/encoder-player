#include "MyCameraWindow.h"

MyCameraWindow::MyCameraWindow(CvCapture* cam, QWidget* parent)
    : QWidget(parent), _writable(false), _images(),
      _cvwidget(new QOpenCVWidget(this)), _camera(cam)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(_cvwidget);
    setLayout(layout);
    resize(600, 400);
    //resize(160, 120);
    startTimer(100);  // 0.1-second timer
}

void MyCameraWindow::start()
{
    _writable = true;
    _images.clear();
    this->show();
}

void MyCameraWindow::stop()
{
    _writable = false;
    this->hide();
}

void MyCameraWindow::timerEvent(QTimerEvent*)
{
    IplImage *image = cvQueryFrame(_camera);

    _cvwidget->putImage(image);

    if (_writable)
	_images.push_back(image);
}
