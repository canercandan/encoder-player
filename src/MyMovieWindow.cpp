#include <QTimerEvent>
#include <QDebug>

#include "MyMovieWindow.h"

MyMovieWindow::MyMovieWindow(QWidget* parent)
    : QWidget(parent), _images(), _position(0), _timerId(-1),
      _cvwidget(new QOpenCVWidget(this))
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(_cvwidget);
    setLayout(layout);
    resize(600, 400);
    //resize(160, 120);

}

void MyMovieWindow::setImages(std::vector< IplImage* >& images)
{
    _images = images;
    _position = 0;

    this->show();
}

void MyMovieWindow::start()
{
    _timerId = startTimer(100);  // 0.1-second timer
}

void MyMovieWindow::stop()
{
    killTimer(_timerId);
}

void MyMovieWindow::timerEvent(QTimerEvent* te)
{
    if (te->timerId() != _timerId)
	{
	    return;
	}

    if (_position >= _images.size())
	{
	    _position = 0;
	    stop();
	}

    //assert(_position < _images.size());

    IplImage* image = _images[_position++];

    _cvwidget->putImage(image);
}
