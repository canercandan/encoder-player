#ifndef PLAYBUTTON_HPP
#define PLAYBUTTON_HPP

#include "myVideoList.hpp"
#include <iostream>
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QContextMenuEvent>
#include <QMainWindow>

namespace   qtInterface
{
    class   playButton : public QWidget
    {
    Q_OBJECT
    private:
        QVBoxLayout *_layout;
        QPushButton *_button;
        myVideoList *_videoList;
    public:
        playButton(QWidget *parent = 0);
    public slots:
        void playSlot();
    };
}

#endif // PLAYBUTTON_HPP
