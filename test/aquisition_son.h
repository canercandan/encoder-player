#ifndef aquisition_H
#define aquisition_H

#include <QPixmap>
#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>

#include <QAudioDeviceInfo>
#include <QAudioInput>

//#include <qaudioinput.h>

class AudioInfo : public QIODevice
{
    Q_OBJECT
public:
    AudioInfo(QObject *parent, QAudioInput *device);
    ~AudioInfo();

    void start();
    void stop();

    int LinearMax();

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

    QAudioInput *input;

private:
    int m_maxValue;

signals:
    void update();
};

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

#endif // !aquisition_H
