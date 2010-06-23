#ifndef PAUSEBUTTON_H
#define PAUSEBUTTON_H

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
    class   pauseButton : public QWidget
    {
    Q_OBJECT
    private:
        QVBoxLayout *_layout;
        QPushButton *_button;
    public:
       pauseButton(QWidget *parent = 0);
   public slots:
       void pauseSlot();
    };
}

#endif // PAUSEBUTTON_H
