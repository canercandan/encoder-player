#ifndef MOVIEPLAYER_H
#define MOVIEPLAYER_H

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "MyCameraWindow.h"
#include "MyMovieWindow.h"

#include <QWidget>
#include <QDebug>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QGridLayout;
class QHBoxLayout;
class QLabel;
class QMovie;
class QSlider;
class QSpinBox;
class QToolButton;
class QVBoxLayout;
QT_END_NAMESPACE

class MoviePlayer : public QWidget
{
    Q_OBJECT

public:
    MoviePlayer(QWidget *parent = 0);
    ~MoviePlayer();

    void openFile(const QString &fileName);

private slots:
    void open();
    void myForward();
    void myStart();
    void myBackward();
    void myRec();
    void goToFrame(int frame);
    void fitToWindow();
    void updateButtons();
    void updateFrameSlider();

private:
    void createControls();
    void createButtons();

    QString currentMovieDirectory;
    QLabel *movieLabel;
    QMovie *movie;
    QToolButton *openButton;
    QToolButton *backwardButton;
    QToolButton *playButton;
    QToolButton *forwardButton;
    QToolButton *pauseButton;
    QToolButton *recButton;
    QToolButton *stopButton;
    QToolButton *quitButton;
    QCheckBox *fitCheckBox;
    QSlider *frameSlider;
    QSpinBox *speedSpinBox;
    QLabel *frameLabel;
    QLabel *speedLabel;

    QGridLayout *controlsLayout;
    QHBoxLayout *buttonsLayout;
    QVBoxLayout *mainLayout;

    MyCameraWindow *cameraWindow;
    CvCapture *camera;

    MyMovieWindow* movieWindow;
};

#endif
