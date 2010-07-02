#ifndef _InputTest_h
#define _InputTest_h

#include <QPixmap>
#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>

#include <QAudioDeviceInfo>
#include <QAudioInput>

#include "audioinput.h"
#include "renderarea.h"

#define BUFFER_SIZE 4096

class InputTest : public QMainWindow
{
    Q_OBJECT
public:
    InputTest();
    ~InputTest();

private slots:
    void refreshDisplay();
    void status();
    void readMore();
    void toggleMode();
    void toggleSuspend();
    void state(QAudio::State s);
    void deviceChanged(int idx);

private:
    AudioInfo *audioinfo;
    QAudioDeviceInfo device;
    QAudioFormat format;
    QAudioInput *audioInput;
    QIODevice *input;
    RenderArea *canvas;

    bool pullMode;

    QPushButton *button;
    QPushButton *button2;
    QComboBox *deviceBox;

    char *buffer;
};

#endif // !_InputTest_h
