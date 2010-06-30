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
    class   PlayButton : public QWidget
    {
    Q_OBJECT
    private:
        QVBoxLayout *_layout;
        QPushButton *_button;
        myVideoList *_videoList;
    public:
        PlayButton(QWidget *parent = 0);
    public slots:
        void playSlot();
    };
}

#endif // PLAYBUTTON_HPP
