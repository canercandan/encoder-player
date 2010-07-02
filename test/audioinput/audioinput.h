#ifndef _AudioInput_h
#define _AudioInput_h

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

#endif // !_AudioInput_h
