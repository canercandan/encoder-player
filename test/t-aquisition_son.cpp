#include <cstring>
#include <QtGui>

#include <stdlib.h>
#include <math.h>

#include <QDebug>
#include <QPainter>
#include <QVBoxLayout>

#include <QAudioDeviceInfo>
#include <QAudioInput>

#include "aquisition_son.h"

#define BUFFER_SIZE 4096

AudioInfo::AudioInfo(QObject *parent, QAudioInput *device)
    :QIODevice(parent)
{
    input = device;

    m_maxValue = 0;
}

AudioInfo::~AudioInfo()
{
}

void AudioInfo::start()
{
    open(QIODevice::WriteOnly);
}

void AudioInfo::stop()
{
    close();
}

qint64 AudioInfo::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data)
    Q_UNUSED(maxlen)

    return 0;
}

qint64 AudioInfo::writeData(const char *data, qint64 len)
{
    int samples = len/2; // 2 bytes per sample
    int maxAmp = 32768; // max for S16 samples
    bool clipping = false;

    m_maxValue = 0;

    qint16 *s = (qint16*)data;

    // sample format is S16LE, only!

    for (int i = 0; i < samples; ++i) {
        qint16 sample = *s;
        s++;
        if (abs(sample) > m_maxValue) m_maxValue = abs(sample);
    }
    // check for clipping
    if (m_maxValue >= (maxAmp - 1))
        clipping = true;

    float value = ((float)m_maxValue/(float)maxAmp);
    if (clipping)
        m_maxValue = 100;
    else
        m_maxValue = (int)(value*100);

    emit update();

    return len;
}

int AudioInfo::LinearMax()
{
    return m_maxValue;
}


InputTest::InputTest()
{
    QWidget *window = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;

    canvas = new RenderArea;
    layout->addWidget(canvas);

    deviceBox = new QComboBox(this);
    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    for(int i = 0; i < devices.size(); ++i)
        deviceBox->addItem(devices.at(i).deviceName(), qVariantFromValue(devices.at(i)));

    connect(deviceBox, SIGNAL(activated(int)), SLOT(deviceChanged(int)));
    layout->addWidget(deviceBox);

    button = new QPushButton(this);
    button->setText(tr("Click for Push Mode"));
    connect(button, SIGNAL(clicked()), SLOT(toggleMode()));
    layout->addWidget(button);

    button2 = new QPushButton(this);
    button2->setText(tr("Click To Suspend"));
    connect(button2, SIGNAL(clicked()), SLOT(toggleSuspend()));
    layout->addWidget(button2);

    window->setLayout(layout);
    setCentralWidget(window);
    window->show();

    buffer = new char[BUFFER_SIZE];

    pullMode = true;

    format.setFrequency(8000);
    format.setChannels(1);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setCodec("audio/pcm");

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning()<<"default format not supported try to use nearest";
        format = info.nearestFormat(format);
    }

    if(format.sampleSize() != 16) {
        qWarning()<<"audio device doesn't support 16 bit samples, example cannot run";
        audioInput = 0;
        button->setDisabled(true);
        button2->setDisabled(true);
        return;
    }

    audioInput = new QAudioInput(format,this);
    connect(audioInput, SIGNAL(notify()), SLOT(status()));
    connect(audioInput, SIGNAL(stateChanged(QAudio::State)), SLOT(state(QAudio::State)));
    audioinfo  = new AudioInfo(this,audioInput);
    connect(audioinfo, SIGNAL(update()), SLOT(refreshDisplay()));
    audioinfo->start();
    audioInput->start(audioinfo);
}

InputTest::~InputTest() {}

void InputTest::status()
{
    qWarning()<<"bytesReady = "<<audioInput->bytesReady()<<" bytes, elapsedUSecs = "<<audioInput->elapsedUSecs()<<", processedUSecs = "<<audioInput->processedUSecs();
}

void InputTest::readMore()
{
    if(!audioInput)
        return;
    qint64 len = audioInput->bytesReady();
    if(len > 4096)
        len = 4096;
    qint64 l = input->read(buffer,len);
    if(l > 0) {
        audioinfo->write(buffer,l);
    }
}

void InputTest::toggleMode()
{
    // Change bewteen pull and push modes
    audioInput->stop();

    if (pullMode) {
        button->setText(tr("Click for Pull Mode"));
        input = audioInput->start();
        connect(input, SIGNAL(readyRead()), SLOT(readMore()));
        pullMode = false;
    } else {
        button->setText(tr("Click for Push Mode"));
        pullMode = true;
        audioInput->start(audioinfo);
    }
}

void InputTest::toggleSuspend()
{
    // toggle suspend/resume
    if(audioInput->state() == QAudio::SuspendedState) {
        qWarning() << "status: Suspended, resume()";
        audioInput->resume();
        button2->setText("Click To Suspend");
    } else if (audioInput->state() == QAudio::ActiveState) {
        qWarning() << "status: Active, suspend()";
        audioInput->suspend();
        button2->setText("Click To Resume");
    } else if (audioInput->state() == QAudio::StoppedState) {
        qWarning() << "status: Stopped, resume()";
        audioInput->resume();
        button2->setText("Click To Suspend");
    } else if (audioInput->state() == QAudio::IdleState) {
        qWarning() << "status: IdleState";
    }
}

void InputTest::state(QAudio::State state)
{
    qWarning() << " state=" << state;
}

void InputTest::refreshDisplay()
{
    canvas->setLevel(audioinfo->LinearMax());
    canvas->repaint();
}

void InputTest::deviceChanged(int idx)
{
    audioinfo->stop();
    audioInput->stop();
    audioInput->disconnect(this);
    delete audioInput;

    device = deviceBox->itemData(idx).value<QAudioDeviceInfo>();
    audioInput = new QAudioInput(device, format, this);
    connect(audioInput, SIGNAL(notify()), SLOT(status()));
    connect(audioInput, SIGNAL(stateChanged(QAudio::State)), SLOT(state(QAudio::State)));
    audioinfo->start();
    audioInput->start(audioinfo);
}

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Audio Input Test");

    InputTest input;
    input.show();

    return app.exec();
}
