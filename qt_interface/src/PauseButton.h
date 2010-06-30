#ifndef PAUSEBUTTON_H
#define PAUSEBUTTON_H

#include <iostream>
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QContextMenuEvent>
#include <QMainWindow>

namespace   qtInterface
{
    class   PauseButton : public QWidget
    {
    Q_OBJECT
    private:
        QVBoxLayout *_layout;
        QPushButton *_button;
    public:
       PauseButton(QWidget *parent = 0);
   public slots:
       void pauseSlot();
    };
}

#endif // PAUSEBUTTON_H
